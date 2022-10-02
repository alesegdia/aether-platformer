#pragma once

#include <secs/secs.h>
#include "../components.h"

class FlipFacingSystem : public secs::TypedEntitySystem<RenderComponent, VelocityComponent>
{
public:
	void process( double delta, const secs::Entity& e, RenderComponent& rendercomponent, VelocityComponent& velocitycomponent )
	{
        float vx = velocitycomponent.velocity.GetX();
        if( vx != 0 )
        {
            rendercomponent.flip = vx < 0;
        }
	}
};	

