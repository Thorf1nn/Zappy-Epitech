#include "Music.hpp"

namespace zappy {
    MusicGame::MusicGame(const std::string path)
        : _path(path) {}

    void MusicGame::load() {
        std::cout << "Loading music: " << _path << std::endl;
        _music = LoadMusicStream(_path.c_str());
    }

    void MusicGame::play() {
        PlayMusicStream(_music);
    }

    void MusicGame::update() {
        UpdateMusicStream(_music);
    }

    void MusicGame::loop(bool loop) {
        _music.looping = loop;
    }

    void MusicGame::stop() {
        StopMusicStream(_music);
    }

    void MusicGame::pause() {
        PauseMusicStream(_music);
    }

    void MusicGame::resume() {
        ResumeMusicStream(_music);
    }

    void MusicGame::setVolume(float volume) {
        SetMusicVolume(_music, volume);
    }

    Music MusicGame::get() const {
        return _music;
    }
}