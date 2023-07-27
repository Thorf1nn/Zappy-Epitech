/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-hugo.eschlimann
** File description:
** Platform
*/

#include "Platform.hpp"

namespace zappy {
    Platform::Platform() : _cube(1.0f, 1.0f, 1.0f), _isElevated(true) {}

    Platform::Platform(Vector3 pos, float size) : _cube(1.0f, 1.0f, 1.0f) {
        _pos = pos;
        _size = size;
        _cubeModel.loadFromMesh(_cube.create());
        _texture.load("sources/gui/assets/stone.png");
        _cubeModel.get().materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture.get();
    }

    Vector3 Platform::getPos() {
        return _pos;
    }

    void Platform::setIndex(int index) {
        _islandIndex = index;
    }

    void Platform::getIndex() {
        std ::cout << _islandIndex << std::endl;
    }

    bool Platform::isElevated() {
        std::cout << "posy" << _pos.y << std::endl;
        if (_pos.y > 0)
            return true;
        return false;
    }

    std::vector<std::unique_ptr<Resource>>& Platform::getResources() {
        return _resources;
    }

    std::unordered_map<std::string, int> Platform::getResourcesQuantity() {
        for (auto& resource : _resources) {
            _resourcesQuantity[resource->getName()]++;
        }
        return _resourcesQuantity;
    }

    BoundingBox Platform::getHitbox() {
        return _hitbox;
    }

    float Platform::getSize() {
        return _size;
    }

    void Platform::onClick() {
        _pos.y += 0.8;
    }

    void Platform::resetPosition(std::vector<Vector3>& allPositions) {
        if (_islandIndex < allPositions.size()) {
            _pos.y = allPositions[_islandIndex].y;
        }
    }

    Platform::~Platform()
    {
    }
}
