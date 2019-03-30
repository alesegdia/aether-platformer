
#include "room.h"

std::shared_ptr<MapLayout> parseLayout(const std::shared_ptr<aether::tilemap::TileMap>& layout)
{
    auto objectLayer = layout->getObjectLayer("layout");
    auto rooms = std::make_shared<MapLayout>();

    auto getRoom = [&rooms] (const std::string& name) -> Room::Shared {
        if( rooms->count(name) == 0 ) {
            (*rooms)[name] = std::make_shared<Room>(name);
        }
        return (*rooms)[name];
    };

    for( auto object : objectLayer->objects() ) {
        assert(object.props.count("connection_1") > 0 && "ROOM HAS NO CONNECTIONS");
        for(int i = 1; true; i++) {
            // build connection key and check if exists
            auto id = std::string("connection_") + std::to_string(i);
            if( object.props.count(id) == 0 ) {
                break;
            }

            auto connection = object.props[id];

            std::vector<std::string> strs;
            aether::math::split(connection, strs, ' ');

            assert(strs.size() == 3 && "INCORRECT NUMBER OF ARGUMENTS");

            // processing room connection
            auto otherRoomName = strs[0];
            auto otherDoorName = strs[1];
            auto myDoorName = strs[2];

            auto myRoom = getRoom(object.name);
            auto otherRoom = getRoom(otherRoomName);
            auto myDoor = myRoom->getDoor(myDoorName);
            auto otherDoor = otherRoom->getDoor(otherDoorName);
            myDoor->connectWith(object.name, otherRoomName, otherDoorName);
            otherDoor->connectWith(otherRoomName, object.name, myDoorName);
        }

        Tmx::Map map;
        assert(object.props.count("path") == 1 && "PATH VARIABLE NOT SET!");
        auto fullpath = layout->getBasePath() + object.props["path"];
        map.ParseFile(fullpath);
        auto tilemap = aether::tilemap::buildMap(map);
        (*rooms)[object.name]->setTilemap(tilemap);
    }

    return rooms;
}
