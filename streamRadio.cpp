#include "streamRadio.h"

#include <iostream>
#include <limits>
#include <map>
#include <vlc/vlc.h>

// Map channel names to their stream URLs.
// (Adjust the URLs if necessary.)
std::map<std::string, std::string> StreamRadio::channels = {
  {"SWR3", "http://liveradio.swr.de/sw282p3/swr3/play.mp3"},
  {"SWR2", "https://d111.rndfnk.com/ard/swr/swr2/live/mp3/256/stream."
          "mp3?aggregator=web&cid=01FC1X4J91VJW1CVH6588MZEE3&sid=2snNflJdy3go"
          "aLzrK94kxMvazTH&token=KcRSFeR4yJ5fmFbsOwHpqp7xThh5F4rnpB-u_LtGoWk&"
          "tvf=KQsERX-OIhhkMTExLnJuZGZuay5jb20"},
  {"Regenbogen", "https://audiotainment-sw.streamabc.net/atsw-reg"
          "enbogen1028-aac-128-7085277?sABC=67n86285%231%23s243103pr27n49q887"
          "10ro643s7ns0r3%23ubzrcntr&mode=preroll&aw_0_1st.skey=1739088499&cb"
          "=820968613&aw_0_req.userConsentV2=CQMj2AAQMj2AAAFADBDEBcFsAP_gAAAA"
          "AAYgIxBFRCpdTWFAMXg1ANsgGYAU1sgRIEQQABCAAyAFABOA8IQAkQECMAQAAAACAQ"
          "AAoRABAAAEAABEBECAAAAEABDEAAAAgAEIIABAAAEQQgJAAAgAAAAAEAAIAAAZEwQA"
          "mQCAIcKEBEAAgIAgCAAAAAABAACFAgMACEAYAAIAAAIAAoBAAgJAMAIAAAEAAQO2gC"
          "AA4AM-AyEB2wBYaADAAEEYhEAGAAIIxCoAMAAQRiGQAYAAgjECgAwABBGIJABgACCM"
          "Q6ADAAEEYiEAGAAIIxEoAMAAQRiKQAYAAgjEWgAwABBGIAAA.YAAAAAAAAAAA&aw_0"
          "_1st.playerid=regenbogen_web&aw_0_1st.1plusxAudience=3u,2j,o&liste"
          "nerid=f243103ce27a49d88710eb643f7af0e3&metaid=f243103ce27a49d88710"
          "eb643f7af0e3&amsparams=playerid:homepage;skey:173908851wq7"},
  {"BadenFM", "https://edge60.streams.baden.fm/badenfm-onair?aggregaqtor"
          "//=badenfm_konsole"},
};

void StreamRadio::startStream(const std::string& channel) {

  // Look up the channel name.
  auto it = channels.find(channel);
  if (it == channels.end()) {
    std::cerr << "Channel \"" << channel << "\" not found." << std::endl;
    return;
  }
  const char* url = it->second.c_str();

  // Create a new libVLC instance.
  inst = libvlc_new(0, nullptr);
  if (!inst) {
    std::cerr << "Failed to create libVLC instance." << std::endl;
    return;
  }

  // Create a new media object from the URL.
  libvlc_media_t* media = libvlc_media_new_location(inst, url);
  if (!media) {
    std::cerr << "Failed to create media object." << std::endl;
    libvlc_release(inst);
    return;
  }

  // Create a media player from the media.
  mp = libvlc_media_player_new_from_media(media);
  libvlc_media_release(media);
  if (!mp) {
    std::cerr << "Failed to create media player." << std::endl;
    libvlc_release(inst);
    return;
  }

  // Start playback.
  if (libvlc_media_player_play(mp) == -1) {
    std::cerr << "Failed to start playback." << std::endl;
    libvlc_media_player_release(mp);
    libvlc_release(inst);
    return;
  }
}

void StreamRadio::stopStream() {
  // Stop playback and release resources.
  libvlc_media_player_stop(mp);
  libvlc_media_player_release(mp);
  libvlc_release(inst);
};
