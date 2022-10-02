#pragma once

#include <secs/secs.h>
#include "../components.h"


class AnimationSystem : public secs::TypedEntitySystem<RenderComponent, AnimationComponent>
{
public:
    void process( double delta, const secs::Entity &e, RenderComponent& render_comp, AnimationComponent& anim_comp ) override
    {
        SECS_UNUSED(delta);
        SECS_UNUSED(e);
        anim_comp.animationData.timer += delta;
        anim_comp.animation->UpdateData( anim_comp.animationData );
        render_comp.texture = anim_comp.animationData.currentFrame->texture;
    }
};
