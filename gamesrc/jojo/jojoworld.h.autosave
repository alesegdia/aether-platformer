#pragma once

#include <aether/aether.h>
#include <secs/secs.h>

class ECSWorld;

namespace jojo {

class JojoFactory;
class JojoECS;


class JojoWorld
{
public:
    JojoWorld();

    void render();
    void update(double delta);

private:
    std::shared_ptr<JojoFactory> m_factory;
    std::shared_ptr<aether::tilemap::TileMap> m_tilemap;
    std::shared_ptr<ECSWorld> m_ecsWorld = nullptr;
    secs::Entity m_playerEntity;

};


}
