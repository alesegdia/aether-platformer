#pragma once

#include <secs/secs.h>
#include "../components.h"

class TilemapCollisionSystem : public secs::TypedEntitySystem<AABBComponent, TransformComponent, TilemapCollisionComponent>
{
public:
    TilemapCollisionSystem()
    {
        SetStepConfiguration(true, false);
    }

    void setCollisionTilemap(std::shared_ptr<aether::tilemap::CollisionTilemap> ct)
    {
        m_collisionTilemap = ct;
    }

    void process( double delta, const secs::Entity& e,
                  AABBComponent& aabbcomponent,
                  TransformComponent& transformcomponent,
                  TilemapCollisionComponent& tcc ) override
    {
        SECS_UNUSED(delta);
        SECS_UNUSED(e);
        SECS_UNUSED(tcc);

        auto& current_position = transformcomponent.position;

        // store previous aabb position to check if the object position was corrected
        auto previous_position = aabbcomponent.aabb.position();

        // try to move the AABB in the tilemap to the dirty_position
        auto ci = m_collisionTilemap->Move(aabbcomponent.aabb,
                                               int(current_position.GetX()),
                                               int(ceil(current_position.GetY())));

        auto center = aabbcomponent.aabb.center();

        if( ci.collision_y )
        {
            current_position.SetY( aabbcomponent.aabb.y() );
        }

        if( ci.collision_x )
        {
            current_position.SetX( aabbcomponent.aabb.x() );
        }

        if( HasComponent<AnimatorComponent>(e) )
        {
            auto& ac = GetComponent<AnimatorComponent>(e);
            ac.onAir = !ci.collision_y || ci.y_collision_direction == -1;
        }

        aabbcomponent.aabb.position(aether::math::Vec2i(current_position.GetX(), current_position.GetY()));

        tcc.lastCollisionInfo = ci;
    }

    void Render ( const secs::Entity& e ) override
    {
        auto& aabbcomp = GetComponent<AABBComponent>(e);
        // aether::graphics::draw_filled_rectangle_centered(aabbcomp.aabb, aether::graphics::Color(uint8_t(0), uint8_t(255), uint8_t(255)));
    }

private:
    std::shared_ptr<aether::tilemap::CollisionTilemap> m_collisionTilemap;

};	



