#pragma once

#include "aether/plugin/platformer/core/roomlayoutgameworld.h"
#include "aether/plugin/platformer/ecs/ecsworld.h"
#include "cortex/cortexentityfactory.h"


namespace cortex {

class CortexEntityFactory;


class CortexWorld : public RoomLayoutGameWorld
{
public:
    CortexWorld();

    ~CortexWorld() override;

    virtual void onRoomCreated ( std::shared_ptr<Room> room ) override;

    virtual secs::Entity makePlayer( float x, float y ) override;

    virtual std::shared_ptr<ECSWorld> createECSWorld(std::shared_ptr<aether::tilemap::TilemapMovementSolver> tilemapMovementSolver, int playerIndex) override;

    void render() override;
private:
    std::shared_ptr<CortexEntityFactory> m_factory;

};


}
