#include "entityfactory.h"

BaseEntityFactory::BaseEntityFactory(secs::Engine &ecsEngine)
    : m_ecsEngine(ecsEngine)
{

}

BaseEntityFactory::~BaseEntityFactory()
= default;

secs::Engine& BaseEntityFactory::world()
{
    return m_ecsEngine;
}

void BaseEntityFactory::addBasicTilemapEntity(secs::Entity e, float x, float y, float w, float h)
{
    auto& transform_comp = addComponent<TransformComponent>(e);
    transform_comp.position.set( x, y );
    auto& aabb_comp = addComponent<AABBComponent>(e);
    aabb_comp.aabb = aether::math::Recti(-w/2, -h/2, w, h);
    auto& hcc = addComponent<HadronCollisionComponent>(e);
    hcc.body = new hadron::Body(x, y, w, h);
    hcc.offset.set(0, 0); //-w/2, -h/2);
    addComponent<VelocityComponent>(e);
    addComponent<TilemapCollisionComponent>(e);
}

