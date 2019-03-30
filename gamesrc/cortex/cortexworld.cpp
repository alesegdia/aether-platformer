#include "cortexworld.h"
#include "cortexecs.h"


namespace cortex {


CortexWorld::CortexWorld()
{
    Tmx::Map map;
    map.ParseFile("assets/maps/main/layout.tmx");
    auto leMap = aether::tilemap::buildMap(map);
    setLayout(parseLayout(leMap));
    goToRoom("medical-supplies", 1000, 1000);
}

CortexWorld::~CortexWorld()
= default;

void CortexWorld::onRoomCreated(Room::Shared room)
{
    // create enemies and stuff game specific here with factory
    for( auto& doorEntry : room->doorsMap() )
    {
        auto& door = doorEntry.second;
        m_factory->makeDoor(door);
    }
}

secs::Entity CortexWorld::makePlayer(float x, float y)
{
    return m_factory->makePlayer(x, y);
}

std::shared_ptr<ECSWorld> CortexWorld::createECSWorld(std::shared_ptr<aether::tilemap::CollisionTilemap> ct, int playerIndex)
{
    auto ecsworld = std::make_shared<cortex::CortexECS>();
    m_factory.reset(new CortexEntityFactory(ecsworld->engine(), playerIndex));
    ecsworld->setCollisionTilemap(ct);
    return std::static_pointer_cast<ECSWorld>(ecsworld);
}


}
