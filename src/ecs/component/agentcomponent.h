#pragma once

#include <cstdint>

#include <aether/aether.h>

struct AgentComponent
{
    bool jump_requested = false;
    aether::math::Vec2<int8_t> requested_direction = aether::math::Vec2<int8_t>(0, 0) ;
    int8_t vertical_requested_direction = 0 ;
};
