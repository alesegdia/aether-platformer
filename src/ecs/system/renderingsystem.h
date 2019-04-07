#pragma once

#include <secs/secs.h>
#include "../components.h"

class RenderingSystem : public secs::EntitySystem
{
public:

    using EntityListIterator = std::list<secs::Entity>::iterator;

    RenderingSystem()
    {
        setStepConfiguration(false, true);
        setNeededComponents<TransformComponent, RenderComponent>();
    }

    void onAdded(const secs::Entity& e) override
    {
        auto order = component<RenderComponent>(e).renderOrder;
        assert(order >= 0 && "ORDER CANT BE NEGATIVE");
        int diff = order - int(m_orderPointers.size()) + 1;
        while(diff > 0) {
            diff--;
            m_entities.emplace_back();
        }
        m_entities[size_t(order)].push_back(e);
    }

    void renderStep() override
    {
        for( auto& renderList : m_entities ) {
            for( auto& entity : renderList ) {
                render(entity);
            }
        }
    }

    void render( const secs::Entity& e ) override
	{
        auto& transformcomponent = component<TransformComponent>(e);
        auto& rendercomponent = component<RenderComponent>(e);
        if( rendercomponent.layer != nullptr ) {
            rendercomponent.layer->render();
        } else {
            const auto& p = transformcomponent.position;
            const auto& o = rendercomponent.render_offset;
            auto w = rendercomponent.texture->clip().w();
            auto h = rendercomponent.texture->clip().h();
            rendercomponent.texture->draw( p.x() - w/2, p.y() - h/2, rendercomponent.flip );
        }
    }

private:
    std::vector<std::vector<secs::Entity>> m_entities;
    std::vector<EntityListIterator> m_orderPointers;

};	

