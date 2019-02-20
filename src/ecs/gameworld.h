#pragma once

#include <secs/secs.h>
#include "systems.h"
#include "entityfactory.h"

class GameWorld
{
public:

    GameWorld(std::shared_ptr<aether::tilemap::CollisionTilemap> ct, Assets& assets);

    void step(double delta );

    void render();

    EntityFactory& factory();

    secs::Engine& engine();

private:

    secs::Engine m_world;
    EntityFactory m_factory;

    RenderingSystem                 m_renderingSystem;
    AnimationSystem                 m_animationSystem;
    HadronCollisionSystem           m_hadronCollisionSystem;
    PlayerControllerSystem          m_playerControllerSystem;
    GravitySystem                   m_gravitySystem;
    MovementSystem                  m_movementSystem;
    TilemapCollisionSystem          m_tilemapCollisionSystem;
    JumperControllerSystem          m_jumperControllerSystem;
    FlipFacingSystem                m_flipFacingSystem;
    AnimatorSystem                  m_animatorSystem;


};
