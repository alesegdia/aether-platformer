#pragma once

#include <aether/aether.h>

#include <fstream>

#include "aether/plugin/platformer/ecs/component/VaniaJumper/VaniaJumperAgentComponent.h"
#include "aether/plugin/platformer/ecs/component/GravityComponent.h"

namespace enerjim {

class EnerjimConfig
{
public:
    
    static const EnerjimConfig& instance();

	int GetWindowWidth() const;
    int GetWindowHeight() const;
    int GetOrthoScale() const;
	const VaniaJumperAgentConfig& GetVaniaJumperAgentConfig() const;
	const GravityConfig& GetGravityConfig() const;
	const std::string& GetStartingMapPath() const;

private:
    EnerjimConfig();

    void LoadLUA();

    int mWindowWidth;
    int mWindowHeight;
    int mOrthoScale;

    VaniaJumperAgentConfig mVaniaJumperAgentConfig;
    GravityConfig mGravityConfig;

    std::string mStartingMapPath;

};


}
