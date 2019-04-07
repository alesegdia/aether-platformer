
#include "jojoecs.h"
#include "ecs/systems.h"

namespace jojo {


JojoECS::JojoECS()
{
    pushSystem<AnimatorSystem>();
    pushSystem<PlayerControllerSystem>();
    pushSystem<GravitySystem>();
    pushSystem<JumperControllerSystem>();
    m_aiAgentDumbWalkerSystem = pushSystem<AIAgentDumbWalkerSystem>();
}

void JojoECS::setCollisionTilemap(std::shared_ptr<aether::tilemap::CollisionTilemap> ct)
{
    ECSWorld::setCollisionTilemap(ct);
    m_aiAgentDumbWalkerSystem->setCollisionTilemap(ct);
}


}
