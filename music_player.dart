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
  List<Uint8List> _audioChunks = []; // Store chunks for debugging

  Future<void> togglePlayPause({
    required Function() onDone,
    required Function(Object) onError,
    required Map<String, String> jsonRequest,
  }) async {
    if (isPlaying) {
      stop();
      return;
    }

    print('Starting music playback...');
    
    // Step 1: Prepare the stream controller
    _byteController = StreamController<Uint8List>.broadcast();
    _audioChunks.clear();

    // Step 2: Connect to the server and send JSON
    _streamHandler = JsonStreamHandler(
      serverIp: serverIp,
      serverPort: serverPort,
      jsonRequest: jsonRequest,
    );

    isPlaying = true;

    // Step 3: Set up and play the audio player BEFORE connecting
    _audioSource = _ChunkedAudioSource(_byteController!.stream);
    
    try {
      await _audioPlayer.setAudioSource(_audioSource!);
      print('Audio source set successfully');
    } catch (e) {
      print('Error setting audio source: $e');
      onError(e);
      return;
    }

    await _streamHandler!.connectAndSend(
      // Audio data callback
      (Uint8List data) {
        print('Received audio chunk: ${data.length} bytes');
        _audioChunks.add(data);
        _byteController?.add(data);
        
        // Start playing after receiving first chunk
        if (_audioChunks.length == 1) {
          _startPlayback();
        }
      },
      onDone: () {
        print('Stream completed. Total chunks received: ${_audioChunks.length}');
        _byteController?.close();
        isPlaying = false;
        onDone();
      },
      onError: (error) {
        print('Stream error: $error');
        _byteController?.close();
        isPlaying = false;
        onError(error);
      },
    );
  }

  Future<void> _startPlayback() async {
    try {
      print('Starting audio playback...');
      await _audioPlayer.play();
      print('Audio player started successfully');
      
      // Monitor playback state
      _audioPlayer.playerStateStream.listen((state) {
        print('Player state: ${state.playing}, ${state.processingState}');
      });
      
    } catch (e) {
      print('Error starting playback: $e');
    }
  }

  void stop() {
    print('Stopping music playback...');
    _audioPlayer.stop();
    _streamHandler?.close();
    _byteController?.close();
    _audioChunks.clear();
    isPlaying = false;
  }
}

class _ChunkedAudioSource extends StreamAudioSource {
  final Stream<Uint8List> byteStream;
  _ChunkedAudioSource(this.byteStream);

  @override
  Future<StreamAudioResponse> request([int? start, int? end]) async {
    print('Audio source request: start=$start, end=$end');
    
    return StreamAudioResponse(
      sourceLength: null,
      contentLength: null,
      offset: start ?? 0,
      stream: byteStream,
      contentType: 'audio/mpeg',
    );
  }
}