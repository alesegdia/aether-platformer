#pragma once

#include <aether/aether.h>


struct AABBComponent
{
    aether::math::Recti aabb;
    aether::math::Vec2i offset = aether::math::Vec2i(0, 0);
};
