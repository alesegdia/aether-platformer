#pragma once

#include <secs/secs.h>
#include "../components.h"

class AIAgentDumbWalkerSystem : public secs::TypedEntitySystem<
        AIAgentDumbWalkerComponent,
        AABBComponent,
        AgentInputComponent,
        VelocityComponent>
{
public:
    void process( double delta,
                  const secs::Entity& e,
                  AIAgentDumbWalkerComponent& aiagentdumbwalkercomponent,
                  AABBComponent& aabbcomponent,
                  AgentInputComponent& aic,
                  VelocityComponent& vc )
	{
        auto y = aabbcomponent.aabb.y2() + 2;
        if( !m_collisionTilemap->isSolidTile(aabbcomponent.aabb.x(), y) )
        {
            aic.x_axis = - aic.x_axis;
        }

        vc.velocity.x(aic.x_axis * aic.horizontal_speed);
	}

    void setCollisionTilemap(std::shared_ptr<aether::tilemap::CollisionTilemap> ct)
    {
        m_collisionTilemap = ct;
    }

private:
    std::shared_ptr<aether::tilemap::CollisionTilemap> m_collisionTilemap;

};	

