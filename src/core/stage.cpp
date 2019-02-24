#include "stage.h"

GameWorld::GameWorld(Assets &assets, std::shared_ptr<MapLayout> layout, const SaveData &saveData)
    : m_assets(assets),
      m_layout(layout)
{
}

void GameWorld::goToRoom(const std::string &name)
{
    assert(m_layout->count(name) == 1 && "Trying to go to unknown room");
    goToRoom((*m_layout)[name]);
}

void GameWorld::render()
{
    m_ecsWorld->render();
}

void GameWorld::update(double delta)
{
    m_ecsWorld->step(delta);
    if( m_ecsWorld->hadron().isHittingDoor() ) {
        auto doorEntity = m_ecsWorld->hadron().hittingDoor();
        auto door = m_ecsWorld->engine().component<DoorComponent>(doorEntity);
        travelThroughDoor(door.door);
    }
}

void GameWorld::travelThroughDoor(const Door &door)
{
    auto name = door.otherRoom();
    assert(m_layout->count(name) == 1);
    goToRoom((*m_layout)[name]);
}

void GameWorld::goToRoom(Room::Shared room)
{
    m_currentRoom = room;
    auto collisionLayer = m_currentRoom->tilemap()->getTileLayer("collision");
    m_collisionTilemap.reset(new aether::tilemap::CollisionTilemap(collisionLayer));
    m_ecsWorld.reset(new ECSWorld(m_collisionTilemap, m_assets));

    for( auto& layer : m_currentRoom->tilemap()->getTileLayers() )
    {
        auto layerEntity = m_ecsWorld->engine().processor().addEntity();
        auto& renderComponent = m_ecsWorld->engine().processor().addComponent<RenderComponent>(layerEntity);
        renderComponent.layer = layer.second;
        renderComponent.renderOrder = layer.second->zOrder();
        m_ecsWorld->engine().processor().addComponent<TransformComponent>(layerEntity).position.set(0, 0);
    }

    m_ecsWorld->factory().makePlayer(300, 300);
}
