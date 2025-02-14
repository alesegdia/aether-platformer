
#include "cortex/cortexecs.h"
#include "aether/plugin/platformer/ecs/systems.h"

namespace cortex {


CortexECS::CortexECS()
{
    pushSystem<AnimatorSystem>();
    pushSystem<JumperPlayerControllerSystem>();
    pushSystem<FreeMoverPlayerControllerSystem>();
    pushSystem<FreeMoverControllerSystem>();
    pushSystem<GravitySystem>();
    pushSystem<JumperAgentControllerSystem>();
}



}
