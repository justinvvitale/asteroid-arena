//
// Created by dim on 3/06/2021.
//

#ifndef I3D_AUDIOPLAYER_H
#define I3D_AUDIOPLAYER_H

#include <string>
#include <iostream>

#if _WIN32

#include <Windows.h>
#include <MMSystem.h>

#endif


class AudioPlayer {
public:
    static void playOnce(const std::string& audioName) {
        // If you don't have windows, you're out of luck lol
#if _WIN32
        if (SOUND_ENABLED) {
            std::string filePath = "data/audio/" + audioName + ".wav";
            PlaySound(filePath.c_str(), NULL, SND_ASYNC);
        }
#endif
    };
};


#endif //I3D_AUDIOPLAYER_H
