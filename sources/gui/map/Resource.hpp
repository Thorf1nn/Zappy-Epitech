/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-hugo.eschlimann
** File description:
** Resource
*/

#ifndef RESOURCE_HPP_
#define RESOURCE_HPP_

#include <ctime>
#include <random>
#include <raylib.h>
#include <raymath.h>
#include <string>

#include "Sprite.hpp"
#include "Utils.hpp"

namespace zappy {
    class Resource {
    public:
        Resource();
        Resource(std::string type, Vector3 position);
        ~Resource() = default;

        void load();
        void updatePath(std::string type);
        void draw();

        std::string getName() const;
        Vector3 getPosition() const;

    private:
        Model _model;
        std::string _modelPath;
        std::string _type;
        Vector3 _position;
        Color _color;
    };
}

#endif /* !RESOURCE_HPP_ */
