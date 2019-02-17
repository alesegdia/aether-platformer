#pragma once

#include <aether/aether.h>

struct AnimationComponent
{
    aether::graphics::Animation* animation = nullptr;
    aether::graphics::AnimationData animationData;
};
