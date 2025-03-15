#include "DemuxFactory.h"
#include "DemuxConfig.h"

#include "Demux/DemuxConfig.h"


namespace Demux {

DemuxFactory::DemuxFactory(secs::Engine &world)
    : BaseEntityFactory(world)
{

}

secs::Entity DemuxFactory::MakePlayer(float x, float y)
{
    secs::Entity player = world().GetEntityProcessor().AddEntity();
    return player;
}

}
