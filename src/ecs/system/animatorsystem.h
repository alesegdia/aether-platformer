#pragma once

#include <secs/secs.h>
#include "../components.h"

class AnimatorSystem : public secs::TypedEntitySystem<RenderComponent, AnimatorComponent>
{
public:
    void OnEntityAdded(const secs::Entity& e) override
    {
        auto& rc = GetComponent<RenderComponent>(e);
        auto& ac = GetComponent<AnimatorComponent>(e);
        rc.sprite->PlayAnimation(ac.groundStandAnimation);
    }

    void process( double delta, const secs::Entity& e, RenderComponent& rc, AnimatorComponent& ac ) override
    {
        if( ac.onAir && rc.sprite->HasAnimation(ac.airAnimation))
        {
            rc.sprite->PlayAnimation(ac.airAnimation);
        }
        else
        {
            if( ac.isWalkingEntity && HasComponent<VelocityComponent>(e) )
            {
                auto& vc = GetComponent<VelocityComponent>(e);
                if( abs(vc.velocity.GetX()) > 0.0001f )
                {
                    rc.sprite->PlayAnimation(ac.groundWalkAnimation);
                    if(ac.slowingDown)
                    {
                        rc.sprite->PlayAnimation(ac.slowDownAnim);
                    }
                    else if(ac.running)
                    {
                        rc.sprite->PlayAnimation(ac.runningAnim);
                    }
                }
                else
                {
                    rc.sprite->PlayAnimation(ac.groundStandAnimation);
                }
            }
        }


	}
};	

