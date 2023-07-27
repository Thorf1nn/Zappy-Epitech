/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-hugo.eschlimann
** File description:
** Animation
*/

#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_

#include "raylib.h"
#include <iostream>
#include <string>
#include <memory>

namespace zappy {
    class Animation {
    public:
        Animation() = default;
        ~Animation();

        void load(const std::string& path, unsigned int& animCount);
        void update(Model model, int frame);

    private:
        unsigned int _animCount;
        std::unique_ptr<ModelAnimation> _modelAnimation;
    };
}

#endif /* !ANIMATION_HPP_ */
