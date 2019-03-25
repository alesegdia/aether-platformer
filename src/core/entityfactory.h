#pragma once

#include <secs/secs.h>
#include "../ecs/components.h"
#include "../constants.h"


class BaseEntityFactory {
public:

    BaseEntityFactory( secs::Engine& ecsEngine );

    virtual ~BaseEntityFactory();

    virtual secs::Entity makePlayer( float x, float y ) = 0 ;

protected:
    secs::Engine& world();

    template <typename ComponentType>
    ComponentType& addComponent( const secs::Entity& e )
    {
        return m_ecsEngine.processor().addComponent<ComponentType>(e);
    }

    void addBasicTilemapEntity(secs::Entity e, float x, float y, float w, float h);

private:
    secs::Engine& m_ecsEngine;
};

