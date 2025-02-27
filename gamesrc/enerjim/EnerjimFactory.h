#pragma once

#include <secs/secs.h>
#include "aether/plugin/platformer/core/entityfactory.h"

class CrazyAgentConfigurationData;

namespace enerjim {


class EnerjimFactory : public BaseEntityFactory
{
public:
    EnerjimFactory( secs::Engine& world, int playerIndex, const CrazyAgentConfigurationData& configData);

    secs::Entity makePlayerFreeMover(float x, float y);
    secs::Entity makePlayer(float x, float y);
    secs::Entity makeCrazyPlayer(float x, float y);
    secs::Entity makeBallEnemy( float x, float y );

private:

    aether::render::AsepriteAnimationData m_playerAnim;
    aether::render::AsepriteAnimationData m_ballEnemyAnim;
	const CrazyAgentConfigurationData& m_config;

};


}
