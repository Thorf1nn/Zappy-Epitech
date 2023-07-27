#include "Animation.hpp"

namespace zappy {
    void Animation::load(const std::string& path, unsigned int& animCount) {
        _animCount = animCount;
        _modelAnimation = std::unique_ptr<ModelAnimation>(LoadModelAnimations(path.c_str(), &_animCount));
    }

    void Animation::update(Model model, int frame) {
        UpdateModelAnimation(model, *_modelAnimation, frame);
    }

    Animation::~Animation() {
        // UnloadModelAnimations(_modelAnimation.get(), _animCount);
    }
}