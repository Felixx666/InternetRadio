#ifndef STREAM_RADIO_H
#define STREAM_RADIO_H

#include <string>
#include <map>
#include <vlc/vlc.h>

class StreamRadio {
public:
  // Store the link for radion channels.
  static std::map<std::string, std::string> channels;

  // Media payer
  libvlc_media_player_t* mp;

  // libVLC instance
  libvlc_instance_t* inst;

  /**
   * Streams the specified radio channel.
   *
   * Valid channel names:
   *  - "swr3"
   *  - "swr2"
   *  - "swr4"
   *  - "Radio Regenbogen"
   *  - "badenfm"
   *
   * The method creates a libVLC instance, starts playback,
   * and blocks until the user presses Enter.
   *
   * @param channel The channel name to stream.
   */
  void startStream(const std::string& channel);

  void stopStream();
};

#endif // STREAM_RADIO_H
