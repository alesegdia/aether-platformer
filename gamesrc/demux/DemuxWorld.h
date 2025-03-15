#pragma once

#include <aether/aether.h>
#include <secs/secs.h>


class ECSWorld;

namespace Demux {


class DemuxFactory;
class DemuxECS;

class DemuxWorld
{
public:
    DemuxWorld() = default;
    int Init();
    void Render();
    void Update(double delta);
    const secs::Engine& GetECSWorld() const;

private:
    std::shared_ptr<DemuxFactory> m_factory;
    std::shared_ptr<ECSWorld> m_ecsWorld = nullptr;
    secs::Entity m_playerEntity;
    std::shared_ptr<aether::tilemap::TileMap> m_tilemap;

};


}
