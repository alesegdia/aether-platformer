
#include "jojoecs.h"
#include "aether/plugin/platformer/ecs/systems.h"

namespace jojo {


JojoECS::JojoECS(int mapHeightInPixels)
	: ECSWorld(mapHeightInPixels)
{
    pushSystem<AnimatorSystem>();
    pushSystem<JumperPlayerControllerSystem>();
    pushSystem<GravitySystem>();
    pushSystem<JumperControllerSystem>();
    pushSystem<FreeMoverControllerSystem>();
    pushSystem<FreeMoverPlayerControllerSystem>();
    m_aiAgentDumbWalkerSystem = pushSystem<AIAgentDumbWalkerSystem>();
}

void JojoECS::setCollisionTilemap(std::shared_ptr<aether::tilemap::CollisionTilemap> ct)
{
    ECSWorld::setCollisionTilemap(ct);
    m_aiAgentDumbWalkerSystem->setCollisionTilemap(ct);
}


}
