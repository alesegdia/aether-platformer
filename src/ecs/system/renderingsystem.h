#pragma once

#include <secs/secs.h>
#include "../components.h"

class RenderingSystem : public secs::EntitySystem
{
public:

    using EntityListIterator = std::list<secs::Entity>::iterator;

    RenderingSystem()
    {
        SetStepConfiguration(false, true);
        SetNeededComponents<TransformComponent, RenderComponent>();
    }

    void OnEntityAdded(const secs::Entity& e) override
    {
        auto order = GetComponent<RenderComponent>(e).renderOrder;
        assert(order >= 0 && "ORDER CANT BE NEGATIVE");
        int diff = order - int(m_orderPointers.size()) + 1;
        while(diff > 0) {
            diff--;
            m_entities.emplace_back();
        }
        m_entities[size_t(order)].push_back(e);
    }

    void RenderStep() override
    {
        for( auto& renderList : m_entities ) {
            for( auto& entity : renderList ) {
                Render(entity);
            }
        }
    }

    void Render( const secs::Entity& e ) override
	{
        auto& transformcomponent = GetComponent<TransformComponent>(e);
        auto& rendercomponent = GetComponent<RenderComponent>(e);
        if( rendercomponent.layer != nullptr ) {
            rendercomponent.layer->Render();
        } else {
            const auto& p = transformcomponent.position;
            const auto& o = rendercomponent.render_offset;
            auto w = rendercomponent.texture.GetClip().w();
            auto h = rendercomponent.texture.GetClip().h();
            rendercomponent.texture.Draw( p.GetX() - w/2, p.GetY() - h/2, rendercomponent.flip );
        }
    }

private:
    std::vector<std::vector<secs::Entity>> m_entities;
    std::vector<EntityListIterator> m_orderPointers;

};	

