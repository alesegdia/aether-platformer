#pragma once

#include <secs/secs.h>
#include "core/entityfactory.h"


namespace jojo {


class JojoFactory : public BaseEntityFactory
{
public:
    JojoFactory( secs::Engine& world, int playerIndex );

    secs::Entity makePlayer( float x, float y );
    secs::Entity makeBallEnemy( float x, float y );

private:

    aether::render::AsepriteAnimationData m_playerAnim;
    aether::render::AsepriteAnimationData m_ballEnemyAnim;
    int m_playerIndex = 0;

};


}
