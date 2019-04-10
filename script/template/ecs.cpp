
#include "##PROJNAMELOWER##ecs.h"
#include "ecs/systems.h"

namespace ##PROJNAMELOWER## {


##PROJNAME##ECS::##PROJNAME##ECS()
{
    pushSystem<AnimatorSystem>();
    pushSystem<PlayerControllerSystem>();
    pushSystem<GravitySystem>();
    pushSystem<JumperControllerSystem>();
    m_aiAgentDumbWalkerSystem = pushSystem<AIAgentDumbWalkerSystem>();
}

void ##PROJNAME##ECS::setCollisionTilemap(std::shared_ptr<aether::tilemap::CollisionTilemap> ct)
{
    ECSWorld::setCollisionTilemap(ct);
    m_aiAgentDumbWalkerSystem->setCollisionTilemap(ct);
}


}
