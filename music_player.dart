import 'dart:async';
import 'dart:convert';
import 'dart:typed_data';
import 'dart:io';
import 'package:just_audio/just_audio.dart';
import 'package:login/json-handler.dart';
import 'package:path_provider/path_provider.dart';

class MusicPlayer {
  static final MusicPlayer _instance = MusicPlayer._internal();
  factory MusicPlayer() => _instance;
  MusicPlayer._internal();

  final String serverIp = '10.0.2.2';
  final int serverPort = 9090;

  JsonStreamHandler? _streamHandler;
  bool isPlaying = false;

  final _audioPlayer = AudioPlayer();
  List<Uint8List> _audioChunks = [];

  Future<void> togglePlayPause({
    required Function() onDone,
    required Function(Object) onError,
    required Map<String, String> jsonRequest,
  }) async {
    if (isPlaying) {
      stop();
      return;
    }

    print('Starting buffered music playback...');
    
    _audioChunks.clear();

    _streamHandler = JsonStreamHandler(
      serverIp: serverIp,
      serverPort: serverPort,
      jsonRequest: jsonRequest,
    );

    isPlaying = true;

    await _streamHandler!.connectAndSend(
      // Audio data callback
      (Uint8List data) {
        print('Received audio chunk: ${data.length} bytes (${_audioChunks.length + 1} chunks total)');
        _audioChunks.add(data);
      },
      onDone: () async {
        print('Stream completed. Total chunks received: ${_audioChunks.length}');
        await _assembleAndPlay();
        onDone();
      },
      onError: (error) {
        print('Stream error: $error');
        isPlaying = false;
        onError(error);
      },
    );
  }

  Future<void> _assembleAndPlay() async {
    try {
      if (_audioChunks.isEmpty) {
        print('No audio chunks received');
        return;
      }

      print('Assembling ${_audioChunks.length} chunks...');
      
      // Calculate total size
      int totalSize = _audioChunks.fold(0, (sum, chunk) => sum + chunk.length);
      print('Total audio data size: $totalSize bytes');

      // Combine all chunks into one buffer
      final combinedData = Uint8List(totalSize);
      int offset = 0;
      for (var chunk in _audioChunks) {
        combinedData.setRange(offset, offset + chunk.length, chunk);
        offset += chunk.length;
      }

      // Save to temporary file
      final tempDir = await getTemporaryDirectory();
      final tempFile = File('${tempDir.path}/temp_audio.mp3');
      await tempFile.writeAsBytes(combinedData);
      
      print('Audio saved to temporary file: ${tempFile.path}');
      print('File size: ${await tempFile.length()} bytes');

      // Play from file
      await _audioPlayer.setFilePath(tempFile.path);
      await _audioPlayer.play();
      
      print('Audio playback started from file');
      
      // Monitor playback state
      _audioPlayer.playerStateStream.listen((state) {
        print('Player state: ${state.playing}, ${state.processingState}');
      });
      
    } catch (e) {
      print('Error assembling and playing audio: $e');
      isPlaying = false;
    }
  }

  void stop() {
    print('Stopping buffered music playback...');
    isPlaying = false;
    _audioPlayer.stop();
    _streamHandler?.close();
    _streamHandler = null;
    _audioChunks.clear();
  }
}