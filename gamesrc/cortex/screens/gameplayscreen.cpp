#include "gameplayscreen.h"

#include "cortex/cortexworld.h"



namespace cortex {


GameplayScreen::GameplayScreen()
= default;

int GameplayScreen::Load()
{
	m_gameWorld.reset(new CortexWorld());
	return 0;
}

int GameplayScreen::Unload()
{
	return 0;
}

void GameplayScreen::Render()
{
    aether::graphics::clear(1, 0, 0);
    m_gameWorld->render();
}


void GameplayScreen::Update(uint64_t delta)
{
    m_gameWorld->update(double(delta));
}


}
