#pragma once

#include "../src/core/gameworld.h"
#include "cortexentityfactory.h"
#include "ecs/ecsworld.h"


class ECSWorld;

namespace cortex {

class CortexEntityFactory;


class CortexWorld : public GameWorld
{
public:
    CortexWorld();

    ~CortexWorld() override;

    virtual void onRoomCreated ( std::shared_ptr<Room> room ) override;

    virtual secs::Entity makePlayer( float x, float y ) override;

    virtual std::shared_ptr<ECSWorld> createECSWorld(std::shared_ptr<aether::tilemap::CollisionTilemap> ct, int playerIndex) override;

private:
    std::shared_ptr<CortexEntityFactory> m_factory;

};


}
