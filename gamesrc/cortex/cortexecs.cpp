
#include "cortex/cortexecs.h"
#include "ecs/systems.h"

namespace cortex {


CortexECS::CortexECS()
{
    pushSystem<AnimatorSystem>();
    pushSystem<PlayerControllerSystem>();
    pushSystem<GravitySystem>();
    pushSystem<JumperControllerSystem>();
}



}
