#pragma once

#include <aether/aether.h>

struct RenderComponent
{
    aether::graphics::TextureRegion texture;
    aether::math::Vec2f render_offset = aether::math::Vec2f(0,0);
    bool flip = false;
    aether::tilemap::Layer::Shared layer = nullptr;
    int renderOrder = 0;
};
