#pragma once

#include <aether/aether.h>


class Door
{
public:
    using Shared = std::shared_ptr<Door>;

    Door(const std::string& name)
        : m_name(name)
    {

    }

    const std::string& name() const
    {
        return m_name;
    }

    void connectWith(const std::string& myRoom, const std::string& otherRoom, const std::string& otherDoor)
    {
        if( m_isConnected ) {
            assert(otherRoom == m_otherRoom && otherDoor == m_otherDoor && "Attempting to connect with different room/door!");
        } else {
            m_otherRoom = otherRoom;
            m_otherDoor = otherDoor;
            m_myRoom = myRoom;
            m_isConnected = true;
        }
    }

    bool isConnected()
    {
        return m_isConnected;
    }

    void setRect(const aether::math::Recti& rect)
    {
        m_rect = rect;
    }

    const aether::math::Recti& getRect() const
    {
        return m_rect;
    }

    const std::string& otherRoom() const
    {
        return m_otherRoom;
    }

    const std::string& otherDoor() const
    {
        return m_otherDoor;
    }

private:
    std::string m_name;
    std::string m_myRoom;
    std::string m_otherRoom;
    std::string m_otherDoor;
    bool m_isConnected = false;
    aether::math::Recti m_rect;

};


class Room
{
public:
    using Shared = std::shared_ptr<Room>;
    using DoorsMap = std::unordered_map<std::string, Door::Shared>;

    Room(const std::string& name)
    {
        m_name = name;
    }

    void setTilemap(std::shared_ptr<aether::tilemap::TileMap> map)
    {
        assert(m_tilemapSet == false);
        m_tilemapSet = true;
        m_tilemap = map;
        auto doorsLayer = m_tilemap->getObjectLayer("doors");
        for( auto door : doorsLayer->objects() ) {
            auto doorName = door.name;
            assert(m_doorsMap.count(doorName) == 1 && "There MUST be ONE door already");
            m_doorsMap[doorName]->setRect(door.aabb);
        }
    }

    Door::Shared getDoor(const std::string& name)
    {
        if( m_doorsMap.count(name) == 0 ) {
            m_doorsMap[name] = std::make_shared<Door>(name);
        }
        return m_doorsMap[name];
    }

    const DoorsMap& doorsMap()
    {
        return m_doorsMap;
    }

    const std::shared_ptr<aether::tilemap::TileMap>& tilemap()
    {
        assert(m_tilemapSet);
        return m_tilemap;
    }

private:
    std::shared_ptr<aether::tilemap::TileMap> m_tilemap;
    DoorsMap m_doorsMap;
    bool m_tilemapSet = false;
    std::string m_name;

};

using MapLayout = std::unordered_map<std::string, Room::Shared>;

std::shared_ptr<MapLayout> parseLayout(std::shared_ptr<aether::tilemap::TileMap> layout);

