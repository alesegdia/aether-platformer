#pragma once

#include <secs/secs.h>
#include "core/entityfactory.h"


namespace jojo {


class JojoEntityFactory : public BaseEntityFactory
{
public:
    JojoEntityFactory( secs::Engine& world, int playerIndex );

    secs::Entity makePlayer( float x, float y );

private:

    aether::graphics::LoadedAnimationData m_playerAnim;
    int m_playerIndex = 0;

};


}
