#pragma once

#include <aether/aether.h>

#include <TmxColor.h>

#include "../assets.h"

#include "../ecs/gameworld.h"

class PlatformerJam;

class GameplayScreen : public aether::core::IScreen
{
public:
    GameplayScreen(PlatformerJam* game);

    void show() final;
    void hide() final;
    void render() final;
    void update(uint64_t delta) final;

private:
    PlatformerJam* m_game;
    aether::tilemap::TileMap m_tileMap;
    aether::tilemap::CollisionTilemap m_collisionTilemap;
    aether::tilemap::TileMapRenderer m_tileMapRenderer;
    GameWorld m_gameWorld;

};
