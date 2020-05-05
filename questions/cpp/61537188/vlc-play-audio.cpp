#include <vlc/vlc.h>

#include <iostream>
#include <thread>
#include <chrono>

int main()
{
    const char* argv[] = { "--no-video" };

    auto inst = libvlc_new( 1, argv );

    const auto location = "<path-to-video-file>.mp4";

    auto vlc_media = libvlc_media_new_path( inst, location );
    auto vlc_player = libvlc_media_player_new_from_media( vlc_media );
    libvlc_media_player_set_nsobject( vlc_player, nullptr );
    libvlc_media_player_play( vlc_player );

    while ( libvlc_media_get_state( vlc_media ) != libvlc_Ended )
    {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for( 1s );
    }

    libvlc_media_player_release( vlc_player );
    libvlc_media_release( vlc_media );
    libvlc_release( inst );

    return 0;
}
