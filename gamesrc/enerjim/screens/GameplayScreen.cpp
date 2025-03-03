#include "gameplayscreen.h"


#include <secs/secs.h>
#include "enerjim/EnerjimWorld.h"

#include "aether/plugin/platformer/ecs/components.h"

#include <imgui.h>

#include "aether/plugin/platformer/ecs/component/TilemapCollisionComponent.h"


namespace enerjim {


GameplayScreen::GameplayScreen()
{

}

int GameplayScreen::Load()
{
	m_gameWorld.reset(new EnerjimWorld());
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
	//aether::render::RenderAABBs();
	// m_gameWorld->DebugTilemap();
}

void GameplayScreen::ImGui()
{
	if (m_gameWorld->IsWorldInitialized())
	{
		auto ecsWorld = m_gameWorld->GetECSWorld();
		ImGuiECS(ecsWorld);
		const auto& tcc = ecsWorld.GetComponent<TilemapCollisionComponent>(m_gameWorld->GetPlayerEntity());
		aether::tilemap::ImGuiDebug(tcc.lastCollisionInfo);
	}
	else
	{
		ImGui::Text("ecsWorld is nullptr");
	}
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
