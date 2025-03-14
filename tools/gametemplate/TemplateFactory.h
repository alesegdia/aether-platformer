#pragma once

#include <secs/secs.h>
#include "aether/plugin/platformer/core/entityfactory.h"

namespace enerjim {


class EnerjimFactory : public BaseEntityFactory
{
public:
    EnerjimFactory( secs::Engine& world, int playerIndex);

    secs::Entity MakePlayer(float x, float y);

private:

    aether::render::AsepriteAnimationData m_playerAnim;
    aether::render::AsepriteAnimationData m_ballEnemyAnim;

};


}
