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
    m_gameWorld.reset(new DemuxGameWorld( parseLayout(leMap), m_game->assets ));
    m_gameWorld->goToRoom("medical-labs", 300, 300);
}

void GameplayScreen::hide()
{

}

void GameplayScreen::render()
{
    aether::graphics::clear(1, 0, 0);
    m_gameWorld->render();

}


void GameplayScreen::update(uint64_t delta)
{
    m_gameWorld->update(double(delta));
}
