#pragma once

#include <secs/secs.h>
#include "aether/plugin/platformer/core/entityfactory.h"

namespace ##GAMENAME## {


class ##GAMENAME##Factory : public BaseEntityFactory
{
public:
    ##GAMENAME##Factory( secs::Engine& world );

    secs::Entity MakePlayer(float x, float y);

private:

};


}
