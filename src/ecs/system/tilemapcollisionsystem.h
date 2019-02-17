#pragma once

#include <secs/secs.h>
#include "../components.h"

class TilemapCollisionSystem : public secs::TypedEntitySystem<AABBComponent, TransformComponent, TilemapCollisionComponent>
{
public:
    TilemapCollisionSystem(aether::tilemap::CollisionTilemap& ct)
        : m_collisionTilemap(ct)
    {
        setStepConfiguration(true, false);
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
        auto ci = m_collisionTilemap.realmove( aabbcomponent.aabb, int(current_position.x()), ceil(current_position.y()) );

        if( ci.collision_x )
        {
            current_position.x( aabbcomponent.aabb.position().x() );
        }

        if( ci.collision_y )
        {
            current_position.y( aabbcomponent.aabb.position().y() );
        }

        tcc.lastCollisionInfo = ci;
    }

    void render ( const secs::Entity& e ) override
    {
        auto& aabbcomp = component<AABBComponent>(e);
        aether::graphics::draw_filled_rectangle(aabbcomp.aabb, aether::graphics::Color(uint8_t(255), uint8_t(0), uint8_t(255)));
    }

private:
    aether::tilemap::CollisionTilemap& m_collisionTilemap;

};	



