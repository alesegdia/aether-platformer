
#include "jojoecs.h"

namespace jojo {


JojoECS::JojoECS()
{
    pushSystem<AnimatorSystem>();
    pushSystem<PlayerControllerSystem>();
    pushSystem<GravitySystem>();
    pushSystem<JumperControllerSystem>();
}


}
