
#include "jojoecs.h"

#include "aether/plugin/platformer/ecs/system/AnimatorSystem.h"
#include "aether/plugin/platformer/ecs/system/GravitySystem.h"
    
#include "aether/plugin/platformer/ecs/system/JumperController/JumperControllerSystem.h"
#include "aether/plugin/platformer/ecs/system/FreeMoverController/FreeMoverControllerSystem.h"
#include "aether/plugin/platformer/ecs/system/AIAgentDumbWalkerSystem.h"

#include "aether/plugin/platformer/ecs/component/RenderComponent.h"
#include "aether/plugin/platformer/ecs/component/GravityComponent.h"
#include "aether/plugin/platformer/ecs/component/AnimatorComponent.h"
#include "aether/plugin/platformer/ecs/component/JumperController/JumperAgentComponent.h"
#include "aether/plugin/platformer/ecs/component/TilemapCollisionComponent.h"
#include "aether/plugin/platformer/ecs/component/PlayerComponent.h"
#include "aether/plugin/platformer/ecs/component/AgentInputComponent.h"
#include "aether/plugin/platformer/ecs/component/VelocityComponent.h"
#include "aether/plugin/platformer/ecs/component/AABBComponent.h"
#include "aether/plugin/platformer/ecs/component/TransformComponent.h"
#include "aether/plugin/platformer/ecs/component/HadronCollisionComponent.h"
#include "aether/plugin/platformer/ecs/component/AIAgentDumbWalkerComponent.h"

    


namespace jojo {


JojoECS::JojoECS()
{
    pushSystem<AnimatorSystem>();
    pushSystem<JumperPlayerControllerSystem>();
    pushSystem<GravitySystem>();
    pushSystem<JumperAgentControllerSystem>();
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
