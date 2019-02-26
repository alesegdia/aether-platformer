#pragma once

#include <aether/aether.h>

#include <TmxColor.h>

#include "../assets.h"

#include "../ecs/ecsworld.h"

#include "../core/gameworld.h"

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
    std::shared_ptr<GameWorld> m_gameWorld;

};
