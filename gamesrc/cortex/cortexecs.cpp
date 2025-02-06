
#include "cortex/cortexecs.h"
#include "aether/plugin/platformer/ecs/systems.h"

namespace cortex {


CortexECS::CortexECS()
{
    pushSystem<AnimatorSystem>();
    pushSystem<PlayerControllerSystem>();
    pushSystem<GravitySystem>();
    pushSystem<JumperControllerSystem>();
}



}
