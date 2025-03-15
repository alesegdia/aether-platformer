#pragma once

#include <secs/secs.h>
#include "aether/plugin/platformer/core/entityfactory.h"

namespace Demux {


class DemuxFactory : public BaseEntityFactory
{
public:
    DemuxFactory( secs::Engine& world );

    secs::Entity MakePlayer(float x, float y);

private:

};


}
