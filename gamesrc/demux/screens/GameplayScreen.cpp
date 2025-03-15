#include "gameplayscreen.h"

#include <secs/secs.h>
#include "Demux/DemuxWorld.h"

namespace Demux {


GameplayScreen::GameplayScreen()
{

}

int GameplayScreen::Load()
{
	m_gameWorld.reset(new DemuxWorld());
	m_gameWorld->Init();

	aether::core::get_input_manager().AddEventOnKeyJustPressed("game", aether::core::KeyCode::N1, [this]() {
		aether::GEngine->ToggleFeature("debugfpscam");
	});


	return 0;
}

int GameplayScreen::Unload()
{
	return 0;
}

void GameplayScreen::Render()
{
    m_gameWorld->Render();
}


void GameplayScreen::Update(uint64_t delta)
{
	if (m_gameWorld == nullptr)
	{
		aether::Logger::LogError() << "GameplayScreen::Update: m_gameWorld is nullptr";
	}
	else
	{
		m_gameWorld->Update(double(delta));
	}
}

void GameplayScreen::ImGui()
{

}


}
