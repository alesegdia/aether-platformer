#include "gameworld.h"
#include "../constants.h"

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
    al_build_transform(&tr, (Config::instance().windowWidth / 2 - 256 / 2) - tc.x(), (Config::instance().windowHeight / 2 - 256 / 2) - tc.y(), 1.0f, 1.0f, 0);
    al_use_transform(&tr);

    m_ecsWorld->render();
}

void GameWorld::update(double delta)
{
    checkStatus();
    m_ecsWorld->step(delta);
    if( m_ecsWorld->hadron().isHittingDoor() ) {
        auto doorEntity = m_ecsWorld->hadron().hittingDoor();
        auto collisionResult = m_ecsWorld->hadron().doorCollisionResult();
        auto door = m_ecsWorld->engine().component<DoorComponent>(doorEntity).door;
        assert(door != nullptr);
        travelThroughDoor(door, collisionResult);
    }
}

void GameWorld::travelThroughDoor(const Door::Shared &door, hadron::CollisionResult& result)
{
    checkStatus();
    auto name = door->otherRoom();
    assert(m_layout->count(name) == 1);
    goToRoom((*m_layout)[name], door, result);
}

const Door& GameWorld::getDoorFromRoom(const std::string& room, const std::string& door)
{
    return *(*m_layout)[room]->getDoor(door);
}

void GameWorld::goToRoom(Room::Shared room, const Door::Shared& door, hadron::CollisionResult& result)
{
    // not using auto cause codelite sucks at guessing shared_ptr's contents
    
    const Door& otherDoor = getDoorFromRoom(door->otherRoom(), door->otherDoor());
    aether::math::Recti doorRect = otherDoor.getRect();
    aether::math::Vec2i spawnPos(0, 0);
    int dy = 25;
    switch(otherDoor.getOrientation()) {
        case Door::Left: 
            spawnPos.set(doorRect.x() + 195, doorRect.y() + dy);
            break;
        case Door::Right:
            spawnPos.set(doorRect.x() - 50, doorRect.y() + dy);
            break;
        case Door::Top:
            spawnPos.set(doorRect.x(), doorRect.y() + 200 + dy);
            break;
        case Door::Bottom:
            spawnPos.set(doorRect.x(), doorRect.y() - 200 + dy);
            break;
    }

    goToRoom(room, spawnPos.x(), spawnPos.y());
}

void GameWorld::goToRoom(Room::Shared room, int x, int y)
{
    checkStatus();

    m_currentRoom = room;
    auto collisionLayer = m_currentRoom->tilemap()->getTileLayer("collision");
    auto playerIndex = m_currentRoom->tilemap()->getObjectLayer("player")->zOrder();
    auto collisionTilemap = std::make_shared<aether::tilemap::CollisionTilemap>(collisionLayer);
    m_ecsWorld = createECSWorld(collisionTilemap, playerIndex);

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
