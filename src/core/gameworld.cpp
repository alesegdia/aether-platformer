#include "gameworld.h"

GameWorld::GameWorld()
{

}

GameWorld::~GameWorld()
{

}

void GameWorld::goToRoom(const std::string &name, int x, int y)
{
    checkStatus();
    assert(m_layout->count(name) == 1 && "Trying to go to unknown room");
    goToRoom((*m_layout)[name], x, y);
}

void GameWorld::render()
{
    checkStatus();
    auto tc = playerPosition();

    ALLEGRO_TRANSFORM tr;
    al_identity_transform(&tr);
    al_build_transform(&tr, 1024/2 -tc.x(), 768/2 - tc.y(), 1.0f, 1.0f, 0);
    al_use_transform(&tr);

    m_ecsWorld->render();
}

void GameWorld::update(double delta)
{
    checkStatus();
    m_ecsWorld->step(delta);
    if( m_ecsWorld->hadron().isHittingDoor() ) {
        auto doorEntity = m_ecsWorld->hadron().hittingDoor();
        auto door = m_ecsWorld->engine().component<DoorComponent>(doorEntity);
        travelThroughDoor(door.door);
    }
}

void GameWorld::travelThroughDoor(const Door &door)
{
    checkStatus();
    auto name = door.otherRoom();
    assert(m_layout->count(name) == 1);
#warning change 300 300 to door position
    goToRoom((*m_layout)[name], 300, 300);
}

void GameWorld::goToRoom(Room::Shared room, int x, int y)
{
    checkStatus();
    m_currentRoom = room;
    auto collisionLayer = m_currentRoom->tilemap()->getTileLayer("collision");
    auto collisionTilemap = std::make_shared<aether::tilemap::CollisionTilemap>(collisionLayer);
    m_ecsWorld = createECSWorld(collisionTilemap);

    for( auto& layer : m_currentRoom->tilemap()->getTileLayers() )
    {
        auto layerEntity = m_ecsWorld->engine().processor().addEntity();
        auto& renderComponent = m_ecsWorld->engine().processor().addComponent<RenderComponent>(layerEntity);
        renderComponent.layer = layer.second;
        renderComponent.renderOrder = layer.second->zOrder();
        m_ecsWorld->engine().processor().addComponent<TransformComponent>(layerEntity).position.set(0, 0);
    }

    m_playerEntity = makePlayer(x, y);
    onRoomCreated(room);
}

DemuxGameWorld::~DemuxGameWorld()
{

}
