#pragma once

#include <secs/secs.h>
#include "../components.h"

class JumperControllerSystem : public secs::TypedEntitySystem<
        JumperAgentComponent,
        VelocityComponent,
        AgentInputComponent,
        TilemapCollisionComponent,
        AnimatorComponent>
{
public:
    void process( double delta, const secs::Entity& e,
                  JumperAgentComponent& jac, /* ONLY TAG */
                  VelocityComponent& vc,
                  AgentInputComponent& aic,
                  TilemapCollisionComponent& tccomp,
                  AnimatorComponent& ac) override
	{
        SECS_UNUSED(delta);
        SECS_UNUSED(e);
        SECS_UNUSED(jac);

        vc.velocity.x(aic.x_axis * aic.horizontal_speed);

        // When jump was just pressed in the last frame and we're on top of a tile, we apply a force up
        if( aic.jump_just_requested && tccomp.lastCollisionInfo.y_collision_direction == 1 )
        {
            vc.velocity.y(aic.jump_force);
        }

        // When we hit by going up, set velocity to zero so it automatically starts to fall as it is expected
        if( tccomp.lastCollisionInfo.collision_y && tccomp.lastCollisionInfo.y_collision_direction == -1 )
        {
            vc.velocity.y(0);
        }

        ac.onAir = ! tccomp.lastCollisionInfo.collision_y && tccomp.lastCollisionInfo.y_collision_direction != 1;
	}
};	

