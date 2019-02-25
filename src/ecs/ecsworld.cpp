#include "gameworld.h"


ECSWorld::ECSWorld(std::shared_ptr<aether::tilemap::CollisionTilemap> ct, Assets& assets)
    : m_factory(m_world, assets),
      m_tilemapCollisionSystem(ct)
{
    m_world.pushSystem(&m_renderingSystem);
    m_world.pushSystem(&m_hadronCollisionSystem);
    m_world.pushSystem(&m_movementSystem);
    m_world.pushSystem(&m_playerControllerSystem);
    m_world.pushSystem(&m_gravitySystem);
    m_world.pushSystem(&m_tilemapCollisionSystem);
    m_world.pushSystem(&m_animatorSystem);
    m_world.pushSystem(&m_animationSystem);
    m_world.pushSystem(&m_jumperControllerSystem);
    m_world.pushSystem(&m_flipFacingSystem);
}

void ECSWorld::step(double delta)
{
    m_world.step( delta );
}

void ECSWorld::render()
{
    m_world.render();
}

EntityFactory& ECSWorld::factory()
{
    return m_factory;
}

secs::Engine &ECSWorld::engine()
{
    return m_world;
}
