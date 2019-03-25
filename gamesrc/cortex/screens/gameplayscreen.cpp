#include "gameplayscreen.h"

#include "cortex/cortexworld.h"



namespace cortex {


GameplayScreen::GameplayScreen()
{

}

void GameplayScreen::show()
{
    m_gameWorld.reset(new CortexWorld());
    
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
