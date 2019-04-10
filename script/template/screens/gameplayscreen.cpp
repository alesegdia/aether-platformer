#include "gameplayscreen.h"

#include "jojo/jojoworld.h"



namespace jojo {


GameplayScreen::GameplayScreen()
= default;

void GameplayScreen::show()
{
    m_gameWorld.reset(new JojoWorld());
    
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


}
