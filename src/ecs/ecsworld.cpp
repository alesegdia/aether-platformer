#include "ecs/ecsworld.h"
#include "ecs/systems.h"

#include <utility>


ECSWorld::ECSWorld()
{
    pushSystem<RenderingSystem>();
    pushSystem<FlipFacingSystem>();
    pushSystem<MovementSystem>();
    m_tilemapCollisionSystem = pushSystem<TilemapCollisionSystem>();
    m_hadronCollisionSystem = pushSystem<HadronCollisionSystem>();
    pushSystem<AnimationSystem>();
}

ECSWorld::~ECSWorld()
= default;

void ECSWorld::setCollisionTilemap(std::shared_ptr<aether::tilemap::CollisionTilemap> ct)
{
    m_tilemapCollisionSystem->setCollisionTilemap(std::move(ct));
}

void ECSWorld::step(double delta)
{
    m_world.Step( delta );
}

void ECSWorld::render()
{
    m_world.Render();
}

secs::Engine &ECSWorld::engine()
{
    return m_world;
}

HadronCollisionSystem &ECSWorld::hadron()
{
    return *m_hadronCollisionSystem;
}
