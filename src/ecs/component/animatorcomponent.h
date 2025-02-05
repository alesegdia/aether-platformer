#pragma once

#include <aether/aether.h>


struct AnimatorComponent
{
    bool onAir = false;
    bool movingHorizontally = false;
	bool isWalkingEntity = true;
	bool running = false;
	bool slowingDown = true;

    std::string airAnimation;
	std::string groundStandAnimation;
	std::string groundWalkAnimation;
	std::string slowDownAnim;
	std::string runningAnim;

};
