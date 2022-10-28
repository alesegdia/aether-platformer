#pragma once

#include <aether/aether.h>


struct AnimatorComponent
{
    bool onAir = false;
    bool movingHorizontally = false;
	bool isWalkingEntity = true;
	bool running = false;
	bool slowingDown = true;

    aether::graphics::Animation* airAnimation;
    aether::graphics::Animation* groundStandAnimation;
	aether::graphics::Animation* groundWalkAnimation;
	aether::graphics::Animation* slowDownAnim;
	aether::graphics::Animation* runningAnim;

};
