#pragma once

#include <secs/secs.h>
#include "../components.h"

class AnimatorSystem : public secs::TypedEntitySystem<AnimationComponent, AnimatorComponent>
{
public:
    void onAdded(const secs::Entity& e) override
    {
        auto& atrc = component<AnimationComponent>(e);
        auto& ac = component<AnimatorComponent>(e);
        atrc.animation = ac.groundStandAnimation;
        atrc.animation->reset(atrc.animationData);
        atrc.animation->updateData(atrc.animationData);
    }
    void process( double delta, const secs::Entity& e, AnimationComponent& animationcomponent, AnimatorComponent& atrc ) override
    {
        if( atrc.onAir && atrc.airAnimation != nullptr )
        {
            animationcomponent.animation = atrc.airAnimation;
        }
        else
        {
            if( atrc.isWalkingEntity && hasComponent<VelocityComponent>(e) )
            {
                auto& vc = component<VelocityComponent>(e);
                if( abs(vc.velocity.x()) > 0.0001f )
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

