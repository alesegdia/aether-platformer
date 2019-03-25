#pragma once


#include "ecs/ecsworld.h"

#include <memory>


namespace cortex {

class CortexECS : public ECSWorld
{
public:
    CortexECS(std::shared_ptr<aether::tilemap::CollisionTilemap> ct);
};


}
