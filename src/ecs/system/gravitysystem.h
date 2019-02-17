#pragma once

#include <secs/secs.h>
#include "../components.h"

class GravitySystem : public secs::TypedEntitySystem<GravityComponent, VelocityComponent>
{
public:
    void process( double delta, const secs::Entity& e,
                  GravityComponent& gravitycomponent,
                  VelocityComponent& velocitycomponent ) override
	{
        float prev_y = velocitycomponent.velocity.y();
        float new_y = prev_y + gravitycomponent.gravityFactor;

        if( new_y > gravitycomponent.fallingVelocityCap )
        {
            new_y = gravitycomponent.fallingVelocityCap;
        }

        velocitycomponent.velocity.y(new_y);
	}
};	

