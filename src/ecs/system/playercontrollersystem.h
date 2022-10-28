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

		auto& atrc = GetComponent<AnimatorComponent>(e);

		bool left = aether::core::is_key_down(aether::core::KeyCode::Left);
		bool right = aether::core::is_key_down(aether::core::KeyCode::Right);
        bool running = aether::core::is_key_down(aether::core::KeyCode::Space);


    	if(running)
        {
			if (left)
			{
				aicomp.x_axis = -aicomp.horizontal_speed * 1.75f;

			}
			else if (right)
			{
				aicomp.x_axis = aicomp.horizontal_speed * 1.75f;
			}

			if(abs(aicomp.x_axis) < aicomp.horizontal_speed * 1.70f)
			{
				aicomp.slowing_down = true;
			}


		}
        else
        {
	        if( left )
	        {
	            aicomp.x_axis = -aicomp.horizontal_speed;
				aicomp.slowing_down = false;

	        }
	        else if( right )
	        {
				aicomp.x_axis = aicomp.horizontal_speed;
				aicomp.slowing_down = false;
	        }
	        else if(!aicomp.slowing_down)
	        {
	            aicomp.x_axis = 0.f;
	        }
		}

		aicomp.x_axis *= 0.96f;
		if (abs(aicomp.x_axis) < 0.2f)
		{
			aicomp.x_axis = 0.f;
			aicomp.slowing_down = false;
		}


        aicomp.jump_just_requested = aether::core::is_key_just_pressed(aether::core::KeyCode::Up);
		aicomp.jump_requested = aether::core::is_key_down(aether::core::KeyCode::Up);
		aicomp.running = running;

		atrc.running = running;
		atrc.slowingDown = aicomp.slowing_down;
	}
};	

