#pragma once

#include <secs/secs.h>
#include "../components.h"

class AnimatorSystem : public secs::TypedEntitySystem<AnimationComponent, AnimatorComponent>
{
public:
    void OnEntityAdded(const secs::Entity& e) override
    {
        auto& atrc = GetComponent<AnimationComponent>(e);
        auto& ac = GetComponent<AnimatorComponent>(e);
        atrc.animation = ac.groundStandAnimation;
        atrc.animation->Reset(atrc.animationData);
        atrc.animation->UpdateData(atrc.animationData);
    }
    void process( double delta, const secs::Entity& e, AnimationComponent& animationcomponent, AnimatorComponent& atrc ) override
    {
        if( atrc.onAir && atrc.airAnimation != nullptr )
        {
            animationcomponent.animation = atrc.airAnimation;
        }
        else
        {
            if( atrc.isWalkingEntity && HasComponent<VelocityComponent>(e) )
            {
                auto& vc = GetComponent<VelocityComponent>(e);
                if( abs(vc.velocity.GetX()) > 0.0001f )
                {
                    animationcomponent.animation = atrc.groundWalkAnimation;
                }
                else
                {
                    animationcomponent.animation = atrc.groundStandAnimation;
                }
            }
        }


	}
};	

