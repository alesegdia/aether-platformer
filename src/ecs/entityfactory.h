#pragma once

#include <secs/secs.h>
#include "components.h"
#include "../assets.h"
#include "../constants.h"


class EntityFactory {
public:

    EntityFactory( secs::Engine& ecsEngine );

    virtual ~EntityFactory();

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

class DemuxEntityFactory : public EntityFactory
{
public:
    DemuxEntityFactory( secs::Engine& world, std::shared_ptr<Assets> assets, int playerIndex );

    secs::Entity makePlayer( float x, float y );
    secs::Entity makeDoor( const Door::Shared& door );

private:

    std::shared_ptr<Assets> m_assets = nullptr;
    aether::graphics::LoadedAnimationData m_playerAnim;
    int m_playerIndex = 0;

};
