#pragma once

#include <aether/aether.h>
#include <secs/secs.h>

class ECSWorld;

namespace ##PROJNAMELOWER## {

class ##PROJNAME##Factory;
class ##PROJNAME##ECS;


class ##PROJNAME##World
{
public:
    ##PROJNAME##World();

    void render();
    void update(double delta);

private:
    std::shared_ptr<##PROJNAME##Factory> m_factory;
    std::shared_ptr<aether::tilemap::TileMap> m_tilemap;
    std::shared_ptr<ECSWorld> m_ecsWorld = nullptr;
    secs::Entity m_playerEntity;

};


}
