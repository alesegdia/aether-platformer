#pragma once

#include <secs/secs.h>
#include "components.h"
#include "../assets.h"


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

    void addBasicTilemapEntity(secs::Entity e, float x, float y, float w, float h)
    {
        auto& transform_comp = addComponent<TransformComponent>(e);
        transform_comp.position.set( x, y );
        transform_comp.position.set( x, y );

        auto& aabb_comp = addComponent<AABBComponent>(e);
        aabb_comp.aabb = aether::math::Recti(0, 0, w, h);

        auto& hcc = addComponent<HadronCollisionComponent>(e);
        hcc.body = new hadron::Body(x, y, w, h);
        hcc.offset.set(0, 0);

        addComponent<VelocityComponent>(e);

        addComponent<TilemapCollisionComponent>(e);
    }

private:
    secs::Engine& m_ecsEngine;
};

class DemuxEntityFactory : public EntityFactory
{
public:
    DemuxEntityFactory( secs::Engine& world, std::shared_ptr<Assets>assets );

    secs::Entity makePlayer( float x, float y );

private:

    std::shared_ptr<Assets> m_assets = nullptr;

};
