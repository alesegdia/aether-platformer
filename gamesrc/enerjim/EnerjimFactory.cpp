#include "EnerjimFactory.h"
#include "EnerjimConfig.h"

#include "aether/plugin/platformer/ecs/component/RenderComponent.h"
#include "aether/plugin/platformer/ecs/component/PlayerComponent.h"
#include "aether/plugin/platformer/ecs/component/AgentInputComponent.h"
#include "aether/plugin/platformer/ecs/component/JumperController/JumperAgentComponent.h"
#include "aether/plugin/platformer/ecs/component/CrazyController/CrazyAgentComponent.h"
#include "aether/plugin/platformer/ecs/component/CrazyController/CrazyAnimatorComponent.h"
#include "aether/plugin/platformer/ecs/component/AnimatorComponent.h"
#include "aether/plugin/platformer/ecs/component/GravityComponent.h"
#include "aether/plugin/platformer/ecs/component/AIAgentDumbWalkerComponent.h"
#include "aether/plugin/platformer/ecs/component/HadronCollisionComponent.h"
#include "aether/plugin/platformer/ecs/system/CrazyController/CrazyControllerSystem.h"

#include "aether/plugin/platformer/ecs/component/VaniaJumper/VaniaJumperAgentComponent.h"
#include "aether/plugin/platformer/ecs/component/VaniaJumper/VaniaJumperAnimatorComponent.h"



namespace enerjim {

EnerjimFactory::EnerjimFactory(secs::Engine &world, int playerIndex, const CrazyAgentConfigurationData& config)
    : BaseEntityFactory(world)
    , m_config(config)
{
    aether::render::AsepriteAnimationLoader animloader;
    m_playerAnim = animloader.Load("assets/enerjim/enerjim-anims.json");
}

secs::Entity EnerjimFactory::MakePlayer(float x, float y)
{
    secs::Entity player = world().GetEntityProcessor().AddEntity();

    addBasicTilemapEntity(player, x, y, 8, 16, 500);

    auto& render_comp = addComponent<RenderComponent>(player);
    render_comp.sprite = aether::GEngine->CreateSpriteNode(glm::fvec2{ 64, 64 });
    render_comp.sprite->LoadAllAnimations(m_playerAnim);
    render_comp.sprite->PlayAnimation("idle");
    render_comp.currentAnimation = "idle";

    addComponent<PlayerComponent>(player);

    auto& apc = addComponent<VaniaJumperAgentComponent>(player);

    auto& atrc = addComponent<VaniaJumperAnimatorComponent>(player);
    /*
    atrc.groundStandAnimation = "stand";
    atrc.groundWalkAnimation = "walk";
    atrc.airAnimation = "jump";
    atrc.runningAnim = "run";
    atrc.slowDownAnim = "stop";
    atrc.dashAirAnimation = "jumpdash";
	atrc.stampingAnimation = "stamped";
    */

    auto& gc = addComponent<GravityComponent>(player);
    gc.gravityFactor = m_config.gravityFactor;
    gc.fallingVelocityCap = m_config.fallingCap;

    return player;
}

}
