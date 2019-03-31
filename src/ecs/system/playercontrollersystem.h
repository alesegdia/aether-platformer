#pragma once

#include <secs/secs.h>
#include "../components.h"

class PlayerControllerSystem : public secs::TypedEntitySystem<PlayerComponent, AgentInputComponent>
{
public:
    void process( double delta, const secs::Entity& e,
                  PlayerComponent& playercomponent,
                  AgentInputComponent& aicomp) override
	{
        SECS_UNUSED(delta);
        SECS_UNUSED(e);
        SECS_UNUSED(playercomponent);

        if( aether::core::is_key_down(aether::core::KeyCode::Left) )
        {
            aicomp.x_axis = -aicomp.horizontal_speed;

        }
        else if( aether::core::is_key_down(aether::core::KeyCode::Right) )
        {
            aicomp.x_axis = aicomp.horizontal_speed;
        }
        else
        {
            aicomp.x_axis = 0.f;
        }

        aicomp.jump_just_requested = aether::core::is_key_just_pressed(aether::core::KeyCode::Up);
        aicomp.jump_requested = aether::core::is_key_down(aether::core::KeyCode::Up);
	}
};	

