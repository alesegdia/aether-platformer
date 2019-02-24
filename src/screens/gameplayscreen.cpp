#include "gameplayscreen.h"

#include "../platformerjam.h"


GameplayScreen::GameplayScreen(PlatformerJam *game)
    :   m_game(game)
{

}

void GameplayScreen::show()
{
    Tmx::Map map;
    map.ParseFile("assets/maps/main/layout.tmx");
    auto leMap = aether::tilemap::buildMap(map);
    m_gameWorld.reset(new GameWorld(m_game->assets, parseLayout(leMap), SaveData()));
    m_gameWorld->goToRoom("medical-labs");
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
    m_gameWorld->render();

}


void GameplayScreen::update(uint64_t delta)
{
    m_gameWorld->update(double(delta));
}
