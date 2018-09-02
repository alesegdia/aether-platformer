#pragma once

#include <aether/aether.h>


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
    aether::collision::Tilemap m_collisionTilemap;
    aether::math::Rect<int> m_playerRect;

};
