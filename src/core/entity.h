#pragma once

#include <aether/aether.h>


class Entity
{
public:

    Entity( aether::graphics::Texture tex, const aether::math::Rect<int>& rect, const aether::math::Vec2i& render_offset )
    {
        m_texture = tex;
        m_rect = rect;
        m_renderOffset = render_offset;
    }

    aether::math::Rect<int>& rect()
    {
        return m_rect;
    }

    aether::math::Vec2i& renderOffset()
    {
        return m_renderOffset;
    }

    void render()
    {

    }

private:
    aether::graphics::Texture m_texture;
    aether::math::Rect<int> m_rect;
    aether::math::Vec2i m_renderOffset;

};
