/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-hugo.eschlimann
** File description:
** Platform
*/

#ifndef PLATFORM_HPP_
#define PLATFORM_HPP_

#include <iostream>
#include <memory>
#include <ostream>
#include <unistd.h>
#include <vector>
#include <unordered_map>

#include "Cube.hpp"
#include "raylib.h"
#include "Resource.hpp"
#include "Sprite.hpp"
#include "Texture.hpp"

namespace zappy {
    class Platform {
        public:
            Platform();
            Platform(Vector3 pos, float size);
            ~Platform();
            BoundingBox getHitbox();
            void setIndex(int index);
            void getIndex();

            float getSize();
            Vector3 getPos();
            std::vector<std::unique_ptr<Resource>>& getResources();
            std::unordered_map<std::string, int> getResourcesQuantity();
            void resetPosition(std::vector<Vector3>& allPositions);
            void onClick();
            bool isElevated();

            Vector3 _pos;
            Sprite _cubeModel;

        private:
            Vector3 _initialPosition;
            size_t _islandIndex;

            Texture _texture;
            BoundingBox _hitbox;
            Cube _cube;
            bool _isElevated;

            float _size;

            std::vector<std::unique_ptr<Resource>> _resources;
            std::unordered_map<std::string, int> _resourcesQuantity;

    };
}

#endif /* !PLATFORM_HPP_ */
