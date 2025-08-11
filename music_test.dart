import 'music_player.dart';

void testMusicPlayer() async {
  print('Testing music player...');
  
  // Example music request - adjust the musicName to match what's in your server's music folder
  Map<String, String> musicRequest = {
    'command': 'MUSIC_REQUEST',
    'musicName': 'song.mp3', // Change this to the actual name of a music file in your server
  };
  
  print('Music request: $musicRequest');
  
  MusicPlayer player = MusicPlayer();
  
  await player.togglePlayPause(
    onDone: () {
      print('Music playback completed!');
    },
    onError: (error) {
      print('Music playback error: $error');
    },
    jsonRequest: musicRequest,
  );
}

// Call this function to test
// testMusicPlayer();