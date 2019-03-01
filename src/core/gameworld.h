#pragma once

#include "room.h"
#include "../ecs/ecsworld.h"


struct SaveData
{
    std::string currentRoom;
    aether::math::Vec2f currentRoomPosition;
};


class GameWorld
{
public:

    GameWorld();
    virtual ~GameWorld();
    void goToRoom(const std::string& name, int x, int y);
    void render();

    void update(double delta);

    const aether::math::Vec2f playerPosition()
    {
        return m_ecsWorld->engine().component<TransformComponent>(m_playerEntity).position;
    }

    const std::shared_ptr<ECSWorld>& ecsWorld()
    {
        return m_ecsWorld;
    }

    virtual void onRoomCreated(Room::Shared room) = 0 ;
    virtual secs::Entity makePlayer(float x, float y) = 0 ;
    
    const Door& getDoorFromRoom(const std::string& room, const std::string& door);

protected:
    void setLayout(std::shared_ptr<MapLayout> layout)
    {
        m_layout = layout;
    }

    const Room::Shared& currentRoom()
    {
        return m_currentRoom;
    }

    virtual std::shared_ptr<ECSWorld> createECSWorld(std::shared_ptr<aether::tilemap::CollisionTilemap> ct, int playerIndex) = 0;

private:

    void checkStatus()
    {
        assert(m_layout != nullptr);
    }

    void travelThroughDoor(const Door::Shared& door, hadron::CollisionResult& result);

    void goToRoom(Room::Shared room, int x, int y);
    void goToRoom(Room::Shared room, const Door::Shared& door, hadron::CollisionResult& result);

    std::shared_ptr<MapLayout> m_layout = nullptr;
    std::shared_ptr<ECSWorld> m_ecsWorld = nullptr;
    std::shared_ptr<aether::tilemap::CollisionTilemap> m_collisionTilemap = nullptr;
    std::shared_ptr<Room> m_currentRoom = nullptr;
    secs::Entity m_playerEntity;

};


class DemuxGameWorld : public GameWorld
{
public:
    DemuxGameWorld(std::shared_ptr<MapLayout> layout, std::shared_ptr<Assets> assets)
        : m_assets(assets)
    {
        setLayout(layout);
    }

    ~DemuxGameWorld() override;

    virtual void onRoomCreated ( Room::Shared room ) override
    {
        // create enemies and stuff game specific here with factory
        for( auto& doorEntry : room->doorsMap() )
        {
            auto& door = doorEntry.second;
            m_factory->makeDoor(door);
        }
    }

    virtual secs::Entity makePlayer( float x, float y ) override
    {
        return m_factory->makePlayer(x, y);
    }

    virtual std::shared_ptr<ECSWorld> createECSWorld(std::shared_ptr<aether::tilemap::CollisionTilemap> ct, int playerIndex) override
    {
        auto ecsworld = std::make_shared<DemuxECSWorld>(ct);
        m_factory.reset(new DemuxEntityFactory(ecsworld->engine(), m_assets, playerIndex));
        return std::static_pointer_cast<ECSWorld>(ecsworld);
    }

private:
    std::shared_ptr<Assets> m_assets;
    std::shared_ptr<DemuxEntityFactory> m_factory;

};
