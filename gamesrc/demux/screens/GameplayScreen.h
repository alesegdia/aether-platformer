#pragma once

#include <aether/aether.h>

#include <secs/secs.h>

class RoomLayoutGameWorld;

namespace Demux {

class DemuxWorld;

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
    std::shared_ptr<DemuxWorld> m_gameWorld = nullptr;

};


}
