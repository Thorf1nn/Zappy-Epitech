/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-hugo.eschlimann
** File description:
** Audio
*/

#ifndef AUDIO_HPP_
#define AUDIO_HPP_

#include "raylib.h"
#include <iostream>
#include <string>

class Audio {
public:
    static void initAudio() {
        InitAudioDevice();
    }

    static void closeAudio() {
        CloseAudioDevice();
    }

    static void setMasterVolume(float volume) {
        SetMasterVolume(volume);
    }

    static Wave loadWave(const std::string &path) {
        return LoadWave(path.c_str());
    }

    static Wave loadWaveFromMemory(const std::string &path, const std::string &data, int dataSize) {
        return LoadWaveFromMemory(path.c_str(), (unsigned char *)data.c_str(), dataSize);
    }

    static Sound loadSound(const std::string &path) {
        return LoadSound(path.c_str());
    }
};

#endif /* !AUDIO_HPP_ */
