/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-hugo.eschlimann
** File description:
** Resource
*/

#include "Resource.hpp"

namespace zappy {
    Resource::Resource(std::string type, Vector3 position) {
        _type = type;

        _position.x = position.x + std::rand() % (5 + 1) - 2.5;
        _position.z = position.z + std::rand() % (5 + 1) - 2.5;
        _position.y = 3.5;

        updatePath(type);
    }

    void Resource::draw() {
        // TO DELETE
    }

    void Resource::updatePath(std::string type)
    {
        _type = type;

        if (type == "thystame")
            _modelPath = "sources/gui/assets/resources/glb/6thystame.glb";
        else if (type == "linemate")
            _modelPath = "sources/gui/assets/resources/glb/1linemate.glb";
        else if (type == "deraumere")
            _modelPath = "sources/gui/assets/resources/glb/2deraumere.glb";
        else if (type == "mendiane")
            _modelPath = "sources/gui/assets/resources/glb/4mendiane.glb";
        else if (type == "phiras")
            _modelPath = "sources/gui/assets/resources/glb/5phiras.glb";
        else if (type == "sibur")
            _modelPath = "sources/gui/assets/resources/glb/3sibur.glb";
        else if (type == "food")
            _modelPath = "sources/gui/assets/resources/glb/oxygen.glb";
    }

    void Resource::load()
    {
        _model = LoadModel(_modelPath.c_str());
        _model.transform = MatrixRotateX(-1.5708);

    }

    std::string Resource::getName() const {
        return _type;
    }

    Vector3 Resource::getPosition() const {
        return _position;
    }
}
