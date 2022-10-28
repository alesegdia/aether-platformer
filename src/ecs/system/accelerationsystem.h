#pragma once

#include <secs/secs.h>
#include "../components.h"

class AccelerationSystem : public secs::TypedEntitySystem<TransformComponent, AccelerationComponent, VelocityComponent>
{
public:
    void process( double delta, const secs::Entity& e,
                  TransformComponent& transformcomponent,
        AccelerationComponent& accelcomponent,
        VelocityComponent& velcomponent)
	{
        SECS_UNUSED(delta);

	}
};

