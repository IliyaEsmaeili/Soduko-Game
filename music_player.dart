import 'dart:async';
import 'dart:convert';
import 'dart:typed_data';
import 'package:just_audio/just_audio.dart';
import 'package:login/json-handler.dart';

class MusicPlayer {
  static final MusicPlayer _instance = MusicPlayer._internal();
  factory MusicPlayer() => _instance;
  MusicPlayer._internal();

  final String serverIp = '10.0.2.2';
  final int serverPort = 9090;

  JsonStreamHandler? _streamHandler;
  bool isPlaying = false;

  final _audioPlayer = AudioPlayer();
  StreamController<Uint8List>? _byteController;
  _ChunkedAudioSource? _audioSource;

  Future<void> togglePlayPause({
    required Function() onDone,
    required Function(Object) onError,
    required Map<String, String> jsonRequest,
  }) async {
    if (isPlaying) {
      stop();
      return;
    }

    // Step 1: Prepare the stream controller
    _byteController = StreamController<Uint8List>.broadcast();

    // Step 2: Connect to the server and send JSON
    _streamHandler = JsonStreamHandler(
      serverIp: serverIp,
      serverPort: serverPort,
      jsonRequest: jsonRequest,
    );

    isPlaying = true;

    await _streamHandler!.connectAndSend(
      // Audio data callback
      (Uint8List data) {
        _byteController?.add(data);
      },
      onDone: () {
        _byteController?.close();
        isPlaying = false;
        onDone();
      },
      onError: (error) {
        _byteController?.close();
        isPlaying = false;
        onError(error);
      },
    );

    // Step 3: Set up and play the audio player
    _audioSource = _ChunkedAudioSource(_byteController!.stream);
    await _audioPlayer.setAudioSource(_audioSource!);
    await _audioPlayer.play();
  }

  void stop() {
    _audioPlayer.stop();
    _streamHandler?.close();
    _byteController?.close();
    isPlaying = false;
  }
}

class _ChunkedAudioSource extends StreamAudioSource {
  final Stream<Uint8List> byteStream;
  _ChunkedAudioSource(this.byteStream);

  @override
  Future<StreamAudioResponse> request([int? start, int? end]) async {
    return StreamAudioResponse(
      sourceLength: null,
      contentLength: null,
      offset: start ?? 0,
      stream: byteStream,
      contentType: 'audio/mpeg',
    );
  }
}