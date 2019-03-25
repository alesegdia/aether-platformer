#pragma once

#include "room.h"
#include <secs/secs.h>
#include <hadron/hadron.h>

class ECSWorld;

class GameWorld
{
public:

    GameWorld();
    virtual ~GameWorld();
    void goToRoom(const std::string& name, int x, int y);
    void render();

    void update(double delta);

    const aether::math::Vec2f playerPosition();

    const std::shared_ptr<ECSWorld>& ecsWorld();

    virtual void onRoomCreated(std::shared_ptr<Room> room) = 0 ;
    virtual secs::Entity makePlayer(float x, float y) = 0 ;
    
    const Door& getDoorFromRoom(const std::string& room, const std::string& door);

protected:
    void setLayout(std::shared_ptr<MapLayout> layout);

    const Room::Shared& currentRoom();

    virtual std::shared_ptr<ECSWorld> createECSWorld(std::shared_ptr<aether::tilemap::CollisionTilemap> ct, int playerIndex) = 0;

private:

    void checkStatus();

    void travelThroughDoor(const Door::Shared& door, hadron::CollisionResult& result);

    void goToRoom(Room::Shared room, int x, int y);
    void goToRoom(Room::Shared room, const Door::Shared& door, hadron::CollisionResult& result);

    std::shared_ptr<MapLayout> m_layout = nullptr;
    std::shared_ptr<ECSWorld> m_ecsWorld = nullptr;
    std::shared_ptr<aether::tilemap::CollisionTilemap> m_collisionTilemap = nullptr;
    std::shared_ptr<Room> m_currentRoom = nullptr;
    secs::Entity m_playerEntity;

};


