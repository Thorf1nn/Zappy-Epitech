#ifndef B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_MUSICGAME_HPP
#define B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_MUSICGAME_HPP

#include <iostream>
#include "raylib.h"

namespace zappy {
    class MusicGame {
    public:
        MusicGame(const std::string path);
        ~MusicGame() = default;

        void load();
        void play();
        void update();
        void stop();
        void pause();
        void resume();
        void loop(bool loop);
        void setVolume(float volume);
        Music get() const;

    private:
        std::string _path;
        Music _music;
    };
}

#endif //B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_MUSICGAME_HPP