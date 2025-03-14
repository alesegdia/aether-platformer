#pragma once

#include <aether/aether.h>
#include <secs/secs.h>


class ECSWorld;

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
    const secs::Engine& GetECSWorld() const;

private:
    std::shared_ptr<##GAMENAME##Factory> m_factory;
    std::shared_ptr<ECSWorld> m_ecsWorld = nullptr;
    secs::Entity m_playerEntity;
    std::shared_ptr<aether::tilemap::TileMap> m_tilemap;

};


}
