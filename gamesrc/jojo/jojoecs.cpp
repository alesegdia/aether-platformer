
#include "jojoecs.h"
#include "aether/plugin/platformer/ecs/systems.h"

namespace jojo {


JojoECS::JojoECS()
{
    pushSystem<AnimatorSystem>();
    pushSystem<JumperPlayerControllerSystem>();
    pushSystem<GravitySystem>();
    pushSystem<JumperControllerSystem>();
    pushSystem<FreeMoverControllerSystem>();
    pushSystem<FreeMoverPlayerControllerSystem>();
    m_aiAgentDumbWalkerSystem = pushSystem<AIAgentDumbWalkerSystem>();
}

void JojoECS::SetTilemapMovementSolver(const std::shared_ptr<aether::tilemap::TilemapMovementSolver>& tilemapMovementSolver)
{
    ECSWorld::SetTilemapMovementSolver(tilemapMovementSolver);
    m_aiAgentDumbWalkerSystem->SetTileCollisionQueryInterface(tilemapMovementSolver->GetCollisionQueryInterface());
}


}
