#pragma once

#include "room.h"
#include "../ecs/gameworld.h"


struct SaveData
{
    std::string currentRoom;
    aether::math::Vec2f currentRoomPosition;
};


class GameWorld
{
public:

    GameWorld(Assets& assets, std::shared_ptr<MapLayout> layout, const SaveData& saveData);

    void goToRoom(const std::string& name);
    void render();

    void update(double delta);

    const secs::Entity& playerEntity()
    {
        return m_playerEntity;
    }

    const std::shared_ptr<ECSWorld>& ecsWorld()
    {
        return m_ecsWorld;
    }


private:

    void travelThroughDoor(const Door& door);

    void goToRoom(Room::Shared room);

    Assets& m_assets;
    std::shared_ptr<MapLayout> m_layout;
    std::shared_ptr<ECSWorld> m_ecsWorld;
    std::shared_ptr<aether::tilemap::CollisionTilemap> m_collisionTilemap;
    std::shared_ptr<Room> m_currentRoom;
    secs::Entity m_playerEntity;

};

