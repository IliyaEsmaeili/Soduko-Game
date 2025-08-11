import 'dart:io';
import 'dart:convert';
import 'dart:typed_data';

class JsonHandler {
  static const String SERVER_IP = '10.0.2.2';
  static const int SERVER_PORT = 9090;
  Map<String, String> json;
  JsonHandler({required this.json});

  Future<Map<String, dynamic>> sendTestRequest() async {
    Socket? socket;
    try {
      socket = await Socket.connect(
        SERVER_IP,
        SERVER_PORT,
        timeout: Duration(seconds: 120),
      );
      socket.setOption(SocketOption.tcpNoDelay, true);

      print(
        'Connected to server: ${socket.remoteAddress.address}:${socket.remotePort}',
      );

      // ساخت درخواست JSON

      String jsonRequest = jsonEncode(json);
      print('Sending JSON: $jsonRequest');

      // ارسال درخواست
      socket.writeln(jsonRequest);
      await socket.flush();

      // خواندن پاسخ
      String jsonResponse = await socket.first.then(
        (data) => utf8.decode(data),
      );
      print('Received JSON: $jsonResponse');

      // تجزیه پاسخ JSON
      Map<String, dynamic> response = jsonDecode(jsonResponse);
      return response;
    } catch (e) {
      print('Error sending request: $e');
      return {'success': false, 'message': 'Network error: $e'};
    } finally {
      if (socket != null) {
        socket.close();
        print('Socket closed.');
      }
    }
  }
}

class JsonStreamHandler {
  final String serverIp;
  final int serverPort;
  final Map<String, String> jsonRequest;

  Socket? _socket;
  String _buffer = ''; // Buffer for incomplete data

  JsonStreamHandler({
    required this.serverIp,
    required this.serverPort,
    required this.jsonRequest,
  });

  Future<void> connectAndSend(
    void Function(Uint8List) onData, {
    Function? onDone,
    Function? onError,
  }) async {
    try {
      _socket = await Socket.connect(
        serverIp,
        serverPort,
        timeout: Duration(seconds: 60),
      );
      _socket!.setOption(SocketOption.tcpNoDelay, true);

      print(
        'Connected to server: ${_socket!.remoteAddress.address}:${_socket!.remotePort}',
      );

      String requestString = jsonEncode(jsonRequest);
      print('Sending JSON request: $requestString');
      _socket!.writeln(requestString);
      await _socket!.flush();

      // Listen for incoming data chunks continuously
      _socket!.listen(
        (List<int> data) {
          try {
            String chunkString = utf8.decode(data);
            _buffer += chunkString;
            
            // Split by newlines to handle complete messages
            List<String> lines = _buffer.split('\n');
            _buffer = lines.removeLast(); // Keep incomplete line in buffer
            
            for (String line in lines) {
              if (line.trim().isEmpty) continue;
              
              print('Processing Base64 chunk: ${line.substring(0, line.length > 100 ? 100 : line.length)}...');

              try {
                // All messages are Base64 strings
                final bytes = base64.decode(line.trim());
                onData(bytes);
              } catch (e) {
                print('Error decoding Base64 chunk: $e');
                onError?.call(e);
              }
            }
          } catch (e) {
            print('Error processing chunk: $e');
            onError?.call(e);
          }
        },
        onDone: () {
          print('Server closed connection');
          onDone?.call();
          close();
        },
        onError: (error) {
          print('Socket error: $error');
          onError?.call(error);
          close();
        },
        cancelOnError: true,
      );
    } catch (e) {
      print('Connection error: $e');
      onError?.call(e);
    }
  }

  void close() {
    _socket?.close();
    _socket = null;
    _buffer = '';
    print('Socket closed.');
  }
}