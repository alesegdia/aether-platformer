#pragma once

#include <aether/aether.h>

struct RenderComponent
{
    std::string currentAnimation;
	aether::scene::ISpriteNode* sprite = nullptr;
};
