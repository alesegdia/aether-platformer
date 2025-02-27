#pragma once

#include <aether/aether.h>

#include <TmxColor.h>

#include <secs/secs.h>

class RoomLayoutGameWorld;

namespace enerjim {

class EnerjimWorld;

class GameplayScreen : public aether::core::IScreen
{
public:
    GameplayScreen();

    int Load() final;
    int Unload() final;
    void Render() final;
    void Update(uint64_t delta) final;
	void ImGui() final;

private:
    void ImGuiECS(const secs::Engine& engine);


    std::shared_ptr<EnerjimWorld> m_gameWorld;

};


}
