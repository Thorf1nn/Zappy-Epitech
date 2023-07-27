/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-hugo.eschlimann
** File description:
** Map
*/

#ifndef B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_MAP_HPP
#define B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_MAP_HPP

#include <cstdlib>
#include <map>
#include <cmath>
#include <memory>
#include <vector>
#include <random>
#include <raylib.h>
#include <iostream>
#include <raymath.h>
#include <unordered_set>

#include <future>

#include "Window.hpp"
#include "Camera.hpp"
#include "Utils.hpp"
#include "Texture.hpp"
#include "Cube.hpp"
#include "Sprite.hpp"
#include "Sphere.hpp"
#include "Infos.hpp"
#include "Platform.hpp"
#include "Player.hpp"
#include "Text.hpp"
#include "Inventory.hpp"
#include "Server.hpp"

namespace zappy {
    class Map {
    public:
        Map();
        ~Map();

        void init(Server& server);
        void update(Server& server);
        void draw();
        void createIslands(Infos &infos);
        void updateResources(Server& server);

        void getState(bool isClickedPlayer);
        void initClickedPlayer(std::shared_ptr<Player> clickedPlayer);

        void draw2D(Server& server);
        void handleClick();
        void setCameraBehave();
        void setCamera(Camera3D camera);

    private:
        Cube _cube;
        bool _created;
        float _timer;
        Cube _backgroundCube[4];

        std::vector<Vector3> _allPositions;
        std::map<std::string, size_t> _resources;
        std::vector<std::shared_ptr<Platform>> _islands;
        std::map<std::string, std::map<int, int>> _resourcesPositions;

        bool _isClicked;
        bool _isClickedPlayer;

        int _lenX;
        int _lenZ;
        int _decayX;
        int _decayZ;

        size_t _platformSize;
        size_t _spaceBetweenPlatforms;
        Vector3 _platformPosition;
        float _clickedIslandX;
        float _clickedIslandZ;
        std::shared_ptr<Platform> _clickedIsland;
        std::shared_ptr<Player> _clickedPlayer;
        Texture2D _cordonates;

        //print resources
        Texture _foodTexture;
        Texture _linemateTexture;
        Texture _deraumereTexture;
        Texture _siburTexture;
        Texture _mendianeTexture;
        Texture _phirasTexture;
        Texture _thystameTexture;

        Text _text;
        Inventory _inventory;
        Texture _texture;
        Infos _infos;

        Model _food;
        Model _linemate;
        Model _deraumere;
        Model _sibur;
        Model _mendiane;
        Model _phiras;
        Model _thystame;

        Camera3D _camera;
        Sprite _cubeModel;
        Sprite _redPlanet;
        Sprite _greyPlanet;
        Vector3  _spherePosition;
        Sprite _backgroundModel[4];

        Texture _mapTexture[2];
        Texture2D _cubeTexture;
        Texture _backgroundTexture;
    };
}

#endif //B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_MAP_HPP

