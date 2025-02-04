#pragma once

#include <aether/aether.h>


struct AnimatorComponent
{
    bool onAir = false;
    bool movingHorizontally = false;
	bool isWalkingEntity = true;
	bool running = false;
	bool slowingDown = true;

    aether::render::Animation* airAnimation;
    aether::render::Animation* groundStandAnimation;
	aether::render::Animation* groundWalkAnimation;
	aether::render::Animation* slowDownAnim;
	aether::render::Animation* runningAnim;

};
