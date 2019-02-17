#include "gameplayscreen.h"

#include "../platformerjam.h"


GameplayScreen::GameplayScreen(PlatformerJam *game)
    :   m_game(game),
        m_tileMap(10, 10, 16, 16, {
                0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,1,0,0,
                0,0,0,0,0,0,1,3,1,0,
                0,0,0,0,0,0,3,3,3,0,
                0,0,0,1,0,0,0,0,3,0,
                0,0,0,3,0,0,0,0,3,0,
                1,1,1,3,1,1,1,1,3,1,
                3,3,3,3,3,3,3,3,3,3,
                }),
        m_collisionTilemap(m_tileMap),
        m_gameWorld(m_collisionTilemap, m_game->assets)
{

}

void GameplayScreen::show()
{
    m_gameWorld.factory().makePlayer(10, 10);
    // TODO: this is a quick fix; this should be initialized in an initialization function just ONCE
    m_tileMap.tileSet() = aether::tilemap::TileSet();
    m_tileMap.tileSet().addTile(0, m_game->assets.tilesetSheet.getFrame(0, 0), aether::tilemap::TileCollisionBehaviour::Empty);
    m_tileMap.tileSet().addTile(1, m_game->assets.tilesetSheet.getFrame(1, 0), aether::tilemap::TileCollisionBehaviour::Solid);
    m_tileMap.tileSet().addTile(2, m_game->assets.tilesetSheet.getFrame(2, 0), aether::tilemap::TileCollisionBehaviour::Empty);
    m_tileMap.tileSet().addTile(3, m_game->assets.tilesetSheet.getFrame(1, 1), aether::tilemap::TileCollisionBehaviour::Solid);
    m_tileMap.tileSet().addTile(4, m_game->assets.tilesetSheet.getFrame(0, 1), aether::tilemap::TileCollisionBehaviour::Empty);
    m_tileMap.tileSet().addTile(5, m_game->assets.tilesetSheet.getFrame(2, 1), aether::tilemap::TileCollisionBehaviour::Empty);
}

void GameplayScreen::hide()
{

}

void GameplayScreen::render()
{
    ALLEGRO_TRANSFORM tr;
    al_identity_transform(&tr);
    al_build_transform(&tr, 0, 0, 2, 2, 0);
    al_use_transform(&tr);

    aether::graphics::clear(1, 0, 0);
    m_tileMapRenderer.render(m_tileMap);
    m_gameWorld.render();

    //Tmx::Color color;
}


void GameplayScreen::update(uint64_t delta)
{
    m_gameWorld.step(delta);
}
