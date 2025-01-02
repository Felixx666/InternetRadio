#include <iostream>
#include <vlc/vlc.h>
#include <limits>

int main(int argc, char* argv[]) {
  // Create a new livVLC instance
  libvlc_instance_t* inst = libvlc_new(0, nullptr);
  if (!inst)  {
    std::cerr << "Failed to create libVLC instance." << std::endl;
    return 1;
  }

  // Define SWR3 radio stream URL (128 kbps MP3)
  const char* swr3_url = "http://liveradio.swr.de/sw282p3/swr3/play.mp3";

  // Create a new media object from the URL
  libvlc_media_t* media = libvlc_media_new_location(inst, swr3_url);
  if (!media) {
    std::cerr << "Failed to create media object." << std::endl;
    libvlc_release(inst);
    return 1;
  }

  // Create a media player from the media
  libvlc_media_player_t* mp = libvlc_media_player_new_from_media(media);
  libvlc_media_release(media);

  if (!mp) {
    std::cerr << "Failed to create media player." << std::endl;
    libvlc_release(inst);
    return 1;
  }

  // Start plaback
  if (libvlc_media_player_play(mp) == -1) {
    std::cerr << "Failed to start playback." << std::endl;
    libvlc_media_player_release(mp);
    libvlc_release(inst);
    return 1;
  }

  std::cout << "playing SWR3... Press Enter to stop." << std::endl;
  // Wait for user input to stop
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  // Stop and release resources
  libvlc_media_player_stop(mp);
  libvlc_media_player_release(mp);
  libvlc_release(inst);

  return 0;
}
