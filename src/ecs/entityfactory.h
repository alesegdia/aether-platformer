#pragma once

#include <secs/secs.h>
#include "components.h"
#include "../assets.h"

class EntityFactory
{
public:

    EntityFactory( secs::Engine& world, Assets& assets );

    secs::Entity makePlayer( float x, float y );

private:

    template <typename ComponentType>
    ComponentType& addComponent( const secs::Entity& e )
    {
        return m_world.processor().addComponent<ComponentType>(e);
    }

    secs::Engine& m_world;
    Assets& m_assets;

};
