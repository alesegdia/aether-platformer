#pragma once

#include <aether/aether.h>


struct TransformComponent
{
    aether::math::Vec2f position = aether::math::Vec2f(0, 0);
    float angle = 0;
};
