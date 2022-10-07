#include "gameplayscreen.h"

#include "jojo/jojoworld.h"



namespace jojo {


GameplayScreen::GameplayScreen()
= default;

int GameplayScreen::Load()
{
	m_gameWorld.reset(new JojoWorld());
	m_gameWorld->Init();
	return 0;
}

int GameplayScreen::Unload()
{
	return 0;
}

void GameplayScreen::Render()
{
    aether::graphics::clear(1, 0, 0);
    m_gameWorld->Render();
}


void GameplayScreen::Update(uint64_t delta)
{
    m_gameWorld->Update(double(delta));
}


}
