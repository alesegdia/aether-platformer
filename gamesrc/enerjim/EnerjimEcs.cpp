
#include "EnerjimEcs.h"

#include "aether/plugin/platformer/ecs/system/AnimatorSystem.h"
#include "aether/plugin/platformer/ecs/system/GravitySystem.h"


#include "aether/plugin/platformer/ecs/system/CrazyController/CrazyControllerSystem.h"
#include "aether/plugin/platformer/ecs/system/CrazyController/CrazyAnimatorSystem.h"

#include "aether/plugin/platformer/ecs/system/JumperController/JumperControllerSystem.h"
#include "aether/plugin/platformer/ecs/system/FreeMoverController/FreeMoverControllerSystem.h"
#include "aether/plugin/platformer/ecs/system/AIAgentDumbWalkerSystem.h"
#include "aether/plugin/platformer/ecs/system/PlayerKeyboardControllerSystem.h"

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
#include "aether/plugin/platformer/ecs/component/CrazyController/CrazyAgentComponent.h"
#include "aether/plugin/platformer/ecs/component/CrazyController/CrazyAnimatorComponent.h"
#include "aether/plugin/platformer/ecs/system/CrazyController/CrazyControllerPlayerSystem.h"

#include "aether/plugin/platformer/ecs/system/VaniaJumper/VaniaJumperControllerSystem.h"
#include "aether/plugin/platformer/ecs/system/VaniaJumper/VaniaJumperAnimatorSystem.h"
#include "aether/plugin/platformer/ecs/component/VaniaJumper/VaniaJumperAgentComponent.h"
#include "aether/plugin/platformer/ecs/component/VaniaJumper/VaniaJumperAnimatorComponent.h"
#include "aether/plugin/platformer/ecs/system/VaniaJumper/VaniaJumperControllerPlayerSystem.h"

    


namespace enerjim {


    EnerjimECS::EnerjimECS(const CrazyAgentConfigurationData& data)
{
    pushSystems<
        AnimatorSystem,
        GravitySystem,
        JumperAgentControllerSystem,
		FreeMoverControllerSystem,
        PlayerKeyboardControllerSystem,
        CrazyAnimatorSystem,
        VaniaJumperAgentControllerSystem,
        VaniaJumperAnimatorSystem,
        VaniaJumperControllerPlayerSystem>();
	pushSystem<CrazyAgentControllerSystem>(data);
    m_aiAgentDumbWalkerSystem = pushSystem<AIAgentDumbWalkerSystem>();
}

void EnerjimECS::SetTilemapMovementSolver(const std::shared_ptr<aether::tilemap::TilemapMovementSolver>& tilemapMovementSolver)
{
    ECSWorld::SetTilemapMovementSolver(tilemapMovementSolver);
    m_aiAgentDumbWalkerSystem->SetTileCollisionQueryInterface(tilemapMovementSolver->GetCollisionQueryInterface());
}


}
