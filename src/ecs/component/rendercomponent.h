#pragma once

#include <aether/aether.h>

struct RenderComponent
{
    aether::render::Animation animation;
	aether::render::AnimationData animationData;
	aether::scene::ISpriteNode* sprite = nullptr;
};
