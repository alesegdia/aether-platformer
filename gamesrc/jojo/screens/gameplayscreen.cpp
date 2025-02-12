#include "gameplayscreen.h"


#include <secs/secs.h>
#include "jojo/jojoworld.h"

#include <imgui.h>



namespace jojo {


GameplayScreen::GameplayScreen()
= default;

int GameplayScreen::Load()
{
	m_gameWorld.reset(new JojoWorld());
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
    // aether::graphics::clear(1.f, 0.f, 0.f);
    m_gameWorld->Render();
	aether::render::RenderAABBs();

}


void GameplayScreen::Update(uint64_t delta)
{
    m_gameWorld->Update(double(delta));
	aether::render::RenderAABBs();

}

void GameplayScreen::ImGui()
{
	auto ecsWorld = m_gameWorld->GetECSWorld();
	ImGuiECS(ecsWorld);
}

void GameplayScreen::ImGuiECS(const secs::Engine& engine)
{
	auto entitySystems = engine.GetAllSystems();

	ImGui::Begin("SECS");
	for (auto entitySystem : entitySystems)
	{
		auto system = entitySystem;
		auto name = system->GetName();
		ImGui::Text("%s", name);
	}
	ImGui::End();

}


}
