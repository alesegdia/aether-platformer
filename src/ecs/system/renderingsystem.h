#pragma once

#include <secs/secs.h>
#include "../components.h"

class RenderingSystem : public secs::EntitySystem
{
public:

    RenderingSystem()
    {
        setStepConfiguration(false, true);
        setNeededComponents<TransformComponent, RenderComponent>();
    }

    void render( const secs::Entity& e ) override
	{
        auto& transformcomponent = component<TransformComponent>(e);
        auto& rendercomponent = component<RenderComponent>(e);
        const auto& p = transformcomponent.position;
        const auto& o = rendercomponent.render_offset;
        rendercomponent.texture->draw( p.x() + o.x() , p.y() + o.y() /*, rendercomponent.flip*/ );
	}
};	

