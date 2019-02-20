#include "gameplayscreen.h"

#include "../platformerjam.h"


GameplayScreen::GameplayScreen(PlatformerJam *game)
    :   m_game(game),
        m_gameWorld(m_collisionTilemap, m_game->assets)
{

}

void GameplayScreen::show()
{
    m_gameWorld.factory().makePlayer(10, 10);
    // TODO: this is a quick fix; this should be initialized in an initialization function just ONCE

    Tmx::Map map;
    map.ParseFile("assets/untitled.tmx");
    m_tileMap = aether::tilemap::buildMap(map);
    m_collisionTilemap = std::make_shared<aether::tilemap::CollisionTilemap>(m_tileMap->getTileLayer("collision"));

    //m_tileMap.tileSet() = aether::tilemap::TileSet();
    //m_tileMap.tileSet().addTile(0, m_game->assets.tilesetSheet.getFrame(0, 0), aether::tilemap::TileCollisionBehaviour::Empty);
    //m_tileMap.tileSet().addTile(1, m_game->assets.tilesetSheet.getFrame(1, 0), aether::tilemap::TileCollisionBehaviour::Solid);
    //m_tileMap.tileSet().addTile(2, m_game->assets.tilesetSheet.getFrame(2, 0), aether::tilemap::TileCollisionBehaviour::Empty);
    //m_tileMap.tileSet().addTile(3, m_game->assets.tilesetSheet.getFrame(1, 1), aether::tilemap::TileCollisionBehaviour::Solid);
    //m_tileMap.tileSet().addTile(4, m_game->assets.tilesetSheet.getFrame(0, 1), aether::tilemap::TileCollisionBehaviour::Empty);
    //m_tileMap.tileSet().addTile(5, m_game->assets.tilesetSheet.getFrame(2, 1), aether::tilemap::TileCollisionBehaviour::Empty);
}

void GameplayScreen::hide()
{

}

void GameplayScreen::render()
{
    ALLEGRO_TRANSFORM tr;
    al_identity_transform(&tr);
    al_build_transform(&tr, 0, 0, 0.25f, 0.25f, 0);
    al_use_transform(&tr);

    aether::graphics::clear(1, 0, 0);
    m_tileMap->render();
    m_gameWorld.render();

    //Tmx::Color color;
}


void GameplayScreen::update(uint64_t delta)
{
    //m_gameWorld.step(delta);
}
