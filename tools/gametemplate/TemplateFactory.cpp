#include "##GAMENAME##Factory.h"
#include "##GAMENAME##Config.h"

#include "##GAMENAME##/##GAMENAME##Config.h"


namespace ##GAMENAME## {

##GAMENAME##Factory::##GAMENAME##Factory(secs::Engine &world)
    : BaseEntityFactory(world)
{

}

secs::Entity ##GAMENAME##Factory::MakePlayer(float x, float y)
{
    secs::Entity player = world().GetEntityProcessor().AddEntity();
    return player;
}

}
