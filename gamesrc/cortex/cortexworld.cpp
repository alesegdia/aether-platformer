#include "cortexworld.h"
#include "cortexecs.h"
#include "cortexconfig.h"

namespace cortex {


CortexWorld::CortexWorld()
{
    Tmx::Map map;
    map.ParseFile("assets/maps/main/layout.tmx");
    // auto leMap = aether::tilemap::BuildMap(map);
    // setLayout(parseLayout(leMap));
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

void CortexWorld::render()
{
    auto tc = playerPosition();

    /*
    ALLEGRO_TRANSFORM tr;
    al_identity_transform(&tr);
    al_build_transform(&tr,
                       float(cortex::CortexConfig::instance().windowWidth / 2) - tc.GetX(),
                       float(cortex::CortexConfig::instance().windowHeight / 2) - tc.GetY(),
                       1.0f, 1.0f, 0);
    al_use_transform(&tr);

    RoomLayoutGameWorld::render();
    */
}


}
