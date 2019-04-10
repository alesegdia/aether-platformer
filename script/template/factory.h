#pragma once

#include <secs/secs.h>
#include "core/entityfactory.h"


namespace ##PROJNAMELOWER## {


class ##PROJNAME##Factory : public BaseEntityFactory
{
public:
    ##PROJNAME##Factory( secs::Engine& world, int playerIndex );

    secs::Entity makePlayer( float x, float y );
    secs::Entity makeBallEnemy( float x, float y );

private:

    aether::graphics::LoadedAnimationData m_playerAnim;
    aether::graphics::LoadedAnimationData m_ballEnemyAnim;
    int m_playerIndex = 0;

};


}
