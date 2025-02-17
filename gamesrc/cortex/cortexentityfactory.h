#pragma once

#include <secs/secs.h>
#include "aether/plugin/platformer/core/entityfactory.h"
#include "aether/plugin/platformer/core/room.h"

namespace cortex {


class CortexEntityFactory : public BaseEntityFactory
{
public:
    CortexEntityFactory( secs::Engine& world, int playerIndex );

    secs::Entity makePlayer( float x, float y );
    secs::Entity makeDoor( const Door::Shared& door );

private:

    aether::render::AsepriteAnimationData m_playerAnim;
    int m_playerIndex = 0;

};


}
