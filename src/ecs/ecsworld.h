#pragma once

#include <aether/aether.h>
#include <secs/secs.h>
#include "../core/entityfactory.h"

class HadronCollisionSystem;
class TilemapCollisionSystem;

class ECSWorld
{
public:

    ECSWorld();
    virtual ~ECSWorld();

    virtual void setCollisionTilemap(std::shared_ptr<aether::tilemap::CollisionTilemap> ct);

    void step(double delta );

    void render();

    secs::Engine& engine();

    HadronCollisionSystem& hadron();

protected:

    template <typename T, typename... Args>
    std::shared_ptr<T> pushSystem(Args... args)
    {
        auto shared = std::make_shared<T>(std::forward(args)...);
        m_world.pushSystem(shared);
        return shared;
    }

private:

    secs::Engine m_world;

    std::shared_ptr<HadronCollisionSystem> m_hadronCollisionSystem;
    std::shared_ptr<TilemapCollisionSystem> m_tilemapCollisionSystem;


};

