#pragma once

#include <aether/aether.h>

struct TilemapCollisionComponent
{
    aether::tilemap::CollisionTilemap::CollisionInfo lastCollisionInfo;
};
