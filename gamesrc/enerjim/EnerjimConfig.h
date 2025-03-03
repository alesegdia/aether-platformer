#pragma once

#include <aether/aether.h>

#include <fstream>

#include "aether/plugin/platformer/ecs/component/VaniaJumper/VaniaJumperAgentComponent.h"
#include "aether/plugin/platformer/ecs/component/GravityComponent.h"

namespace enerjim {

class EnerjimConfig
{
public:
    
    static const EnerjimConfig& instance()
    {
        static EnerjimConfig config;
        return config;
    }

	int GetWindowWidth() const;

    int GetWindowHeight() const;

    int GetOrthoScale() const;
    
	const VaniaJumperAgentConfig& GetVaniaJumperAgentConfig() const
	{
		return mVaniaJumperAgentConfig;
	}

	const GravityConfig& GetGravityConfig() const
	{
		return mGravityConfig;
	}

	const std::string& GetStartingMapPath() const
	{
		return mStartingMapPath;
	}

private:
    EnerjimConfig();

    void LoadJSON();

    void LoadLUA();

    int mWindowWidth;
    int mWindowHeight;
    int mOrthoScale;

    VaniaJumperAgentConfig mVaniaJumperAgentConfig;
    GravityConfig mGravityConfig;

    std::string mStartingMapPath;

};


}
