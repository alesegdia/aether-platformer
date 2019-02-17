#pragma once

#include <aether/aether.h>


struct AnimatorComponent
{
    bool onAir = false;
    bool movingHorizontally = false;
    bool isWalkingEntity = true;

    aether::graphics::Animation* airAnimation;
    aether::graphics::Animation* groundStandAnimation;
    aether::graphics::Animation* groundWalkAnimation;
};
