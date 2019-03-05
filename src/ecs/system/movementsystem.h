#pragma once

#include <secs/secs.h>
#include "../components.h"

class MovementSystem : public secs::TypedEntitySystem<TransformComponent, VelocityComponent>
{
public:
    void process( double delta, const secs::Entity& e,
                  TransformComponent& transformcomponent,
                  VelocityComponent& velocitycomponent )
	{
        SECS_UNUSED(delta);
        const auto& v = transformcomponent.position;
        transformcomponent.position.translate( velocitycomponent.velocity );
	}
};

