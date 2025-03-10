#include "jojofactory.h"
#include "jojoconfig.h"

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



namespace jojo {

JojoFactory::JojoFactory(secs::Engine &world, int playerIndex, const CrazyAgentConfigurationData& config)
    : BaseEntityFactory(world)
    , m_config(config)
{
    aether::render::AsepriteAnimationLoader animloader;
    m_playerAnim = animloader.Load("assets/jojo/jojo.json");
    m_ballEnemyAnim = animloader.Load("assets/jojo/enemyball.json");
}

secs::Entity JojoFactory::makePlayerFreeMover(float x, float y)
{
    secs::Entity player = world().GetEntityProcessor().AddEntity();

    addBasicTilemapEntity(player, x, y, 20, 16, 500);

    auto& render_comp = addComponent<RenderComponent>(player);
    render_comp.sprite = aether::GEngine->CreateSpriteNode(glm::fvec2{ 32, 32 });
    render_comp.sprite->LoadAllAnimations(m_playerAnim);
    render_comp.sprite->PlayAnimation("stand");
    render_comp.currentAnimation = "stand";

    addComponent<PlayerComponent>(player);

    addComponent<AgentInputComponent>(player);

	auto& apc = addComponent<AgentParamsComponent>(player);
    apc.horizontalSpeed = m_config.walkSpeed;
    apc.jumpForce = m_config.jumpForce;

    addComponent<FreeMoverAgentComponent>(player);

    auto& atrc = addComponent<AnimatorComponent>(player);
    atrc.groundStandAnimation = "stand";
    atrc.groundWalkAnimation = "walk";
    atrc.airAnimation = "jump";
    atrc.runningAnim = "run";
    atrc.slowDownAnim = "stop";
    atrc.dashAirAnimation = "jumpdash";

    auto& gc = addComponent<GravityComponent>(player);
    gc.SetConfig({ m_config.gravityFactor, m_config.fallingCap });

    return player;
}

secs::Entity JojoFactory::makePlayer(float x, float y)
{
    secs::Entity player = world().GetEntityProcessor().AddEntity();

    addBasicTilemapEntity(player, x, y, 20, 16, 500);

    auto& render_comp = addComponent<RenderComponent>(player);
    render_comp.sprite = aether::GEngine->CreateSpriteNode(glm::fvec2{ 32, 32 });
    render_comp.sprite->LoadAllAnimations(m_playerAnim);
    render_comp.sprite->PlayAnimation("stand");
    render_comp.currentAnimation = "stand";

    addComponent<PlayerComponent>(player);
    
    addComponent<AgentInputComponent>(player);
    
    auto& apc = addComponent<AgentParamsComponent>(player);
    apc.horizontalSpeed = m_config.walkSpeed;
    apc.jumpForce = m_config.jumpForce;
    
    addComponent<JumperAgentComponent>(player);
    auto& atrc = addComponent<AnimatorComponent>(player);
    atrc.groundStandAnimation = "stand";
    atrc.groundWalkAnimation = "walk";
    atrc.airAnimation = "jump";
    atrc.runningAnim = "run";
    atrc.slowDownAnim = "stop";
    atrc.dashAirAnimation = "jumpdash";

    auto& gc = addComponent<GravityComponent>(player);
    gc.SetConfig({ m_config.gravityFactor, m_config.fallingCap });

	addComponent<JumperAgentComponent>(player);

    return player;
}



secs::Entity JojoFactory::makeCrazyPlayer(float x, float y)
{
    secs::Entity player = world().GetEntityProcessor().AddEntity();

    addBasicTilemapEntity(player, x, y, 8, 16, 500);

    auto& render_comp = addComponent<RenderComponent>(player);
    render_comp.sprite = aether::GEngine->CreateSpriteNode(glm::fvec2{ 32, 32 });
    render_comp.sprite->LoadAllAnimations(m_playerAnim);
    render_comp.sprite->PlayAnimation("stand");
    render_comp.currentAnimation = "stand";

    addComponent<PlayerComponent>(player);

    auto& apc = addComponent<CrazyAgentComponent>(player);

    auto& atrc = addComponent<CrazyAnimatorComponent>(player);
    atrc.groundStandAnimation = "stand";
    atrc.groundWalkAnimation = "walk";
    atrc.airAnimation = "jump";
    atrc.runningAnim = "run";
    atrc.slowDownAnim = "stop";
    atrc.dashAirAnimation = "jumpdash";
	atrc.stampingAnimation = "stamped";

    auto& gc = addComponent<GravityComponent>(player);
    gc.SetConfig({ m_config.gravityFactor, m_config.fallingCap });

    addComponent<JumperAgentComponent>(player);

    return player;
}




secs::Entity JojoFactory::makeBallEnemy(float x, float y)
{
    auto entity = world().GetEntityProcessor().AddEntity();

    addBasicTilemapEntity(entity, x, y, 20, 16, 500);

    auto& render_comp = addComponent<RenderComponent>(entity);
    render_comp.currentAnimation = "walk";
	render_comp.sprite = aether::GEngine->CreateSpriteNode(glm::fvec2{ 32, 32 });
	render_comp.sprite->LoadAllAnimations(m_ballEnemyAnim);
	render_comp.sprite->PlayAnimation("walk");

    auto& aic = addComponent<AgentInputComponent>(entity);
    aic.xAxis = 1;

	auto& apc = addComponent<AgentParamsComponent>(entity);
    apc.horizontalSpeed = 0.5f;

    auto& atrc = addComponent<AnimatorComponent>(entity);
    atrc.groundStandAnimation = "walk";
    atrc.groundWalkAnimation = "walk";
    atrc.airAnimation = "walk";

    addComponent<AIAgentDumbWalkerComponent>(entity);

    return entity;

}


}
