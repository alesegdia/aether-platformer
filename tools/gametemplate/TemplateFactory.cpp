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

#include "enerjim/EnerjimConfig.h"

using OnFinishCallback = std::function<void(float)>;
using OnStepCallback = std::function<void(float)>;

class AnimationSequenceKeyFrame
{
public:
	std::string animation = "";
	float loopDuration = 0.f;
	aether::render::Animation::WrapMode wrapMode = aether::render::Animation::WrapMode::Once;
};

class AnimationSequenceKeyFrameData
{
public:
	std::vector<aether::render::AnimationData> animationData;
    int currentKeyFrame = 0;
	std::string animation;
	float durationInSeconds;
	OnFinishCallback onFinish = nullptr;
	OnStepCallback onStepCallback = nullptr;
};

class AnimationSequence
{
public:
	void AddKeyFrame(
		const std::string& animation,
		float durationInSeconds,
		aether::render::Animation::WrapMode wrapMode)
	{
		m_totalSequenceDuration += durationInSeconds;
		//m_keyFrames.push_back({ animation, durationInSeconds, onFinish, onStepCallback, wrapMode });
	}

	AnimationSequenceKeyFrameData Create()
	{
		AnimationSequenceKeyFrameData animationInstance;
		animationInstance.currentKeyFrame = 0;
		animationInstance.durationInSeconds = m_totalSequenceDuration;
		animationInstance.animation = m_keyFrames[0].animation;
		return animationInstance;
	}

	void Step(AnimationSequenceKeyFrameData& animationInstance, float deltaInSeconds)
	{
		const auto& currentKeyframe = m_keyFrames[animationInstance.currentKeyFrame];
		auto animation = currentKeyframe.animation;
	}


private:
	aether::render::AnimationData m_animationData;
	std::vector<AnimationSequenceKeyFrame> m_keyFrames;
	
	float m_totalSequenceDuration = 0.f;

};

namespace enerjim {

EnerjimFactory::EnerjimFactory(secs::Engine &world, int playerIndex)
    : BaseEntityFactory(world)
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
	render_comp.offset = glm::fvec2{ 0, 7 };

    addComponent<PlayerComponent>(player);

    auto& apc = addComponent<VaniaJumperAgentComponent>(player);
    apc.SetConfig(EnerjimConfig::instance().GetVaniaJumperAgentConfig());

    auto& atrc = addComponent<VaniaJumperAnimatorComponent>(player);
    atrc.idleAnim = "idle";
    atrc.walkAnim = "walk";
    atrc.jumpAnim = "jumping";

    auto& gc = addComponent<GravityComponent>(player);
    gc.SetConfig(EnerjimConfig::instance().GetGravityConfig());

    return player;
}

}
