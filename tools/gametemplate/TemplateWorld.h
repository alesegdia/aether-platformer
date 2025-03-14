#pragma once

#include <aether/aether.h>
#include <secs/secs.h>

#include "aether/render/platformerscroller.h"

class ECSWorld;
class CrazyAgentConfigurationData;

namespace ##GAMENAME## {

class ##GAMENAME##Factory;
class ##GAMENAME##ECS;


class ##GAMENAME##World
{
public:
    ##GAMENAME##World() = default;
    int Init();
    void Render();
    void Update(double delta);
    int LoadMapFromLua(Tmx::Map& map);
    bool IsWorldInitialized() const
    {
        return m_ecsWorld != nullptr;
    }
    const secs::Engine& GetECSWorld() const;
    void DebugTilemap();
    secs::Entity GetPlayerEntity() const
    {
		return m_playerEntity;
    }

    void DoPlatformerScrolling(float deltaInSeconds);
	void DoTopDownScrolling();
	void DoDirectScrolling();

private:
    std::shared_ptr<##GAMENAME##Factory> m_factory;
    std::shared_ptr<ECSWorld> m_ecsWorld = nullptr;
    secs::Entity m_playerEntity;
	std::shared_ptr<aether::render::PlatformerScroller> m_platformerScroll;
	std::shared_ptr<aether::render::TopDownMapScroller> m_topDownScroll;
	std::shared_ptr<aether::render::DirectScroller> m_directScroller;
    std::shared_ptr<aether::tilemap::TileMap> m_tilemap;
    std::shared_ptr<CrazyAgentConfigurationData> m_data;

};


}
