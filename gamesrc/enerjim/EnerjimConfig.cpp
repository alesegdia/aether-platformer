#pragma once

#include "EnerjimConfig.h"


#include "aether/lua/helpers.h"


namespace {
	static const char* kWalkSpeedParamName = "walkSpeed";
	static const char* kJumpForceParamName = "jumpForce";
	static const char* kGravityFactorParamName = "gravityFactor";
	static const char* kFallingCapParamName = "fallingCap";
	static const char* kCoyoteTimeParamName = "coyoteTime";
	static const char* kNumberOfJumpsParamName = "numberOfJumps";
}

namespace enerjim {

    int EnerjimConfig::GetWindowWidth() const
    {
        return mWindowWidth;
    }

    int EnerjimConfig::GetWindowHeight() const
    {
        return mWindowHeight;
    }

    int EnerjimConfig::GetOrthoScale() const
    {
        return mOrthoScale;
    }

    EnerjimConfig::EnerjimConfig()
    {
        LoadJSON();
        LoadLUA();
    }

    void EnerjimConfig::LoadJSON()
    {
        std::string error;

        std::ifstream t("assets/enerjim/configs.json");
        std::stringstream buffer;
        buffer << t.rdbuf();

        auto result = json11::Json::parse(buffer.str(), error);
        std::cout << error << std::endl;
        mWindowWidth = result["windowWidth"].int_value();
        mWindowHeight = result["windowHeight"].int_value();
        mOrthoScale = result["orthoScale"].int_value();
    }

    void EnerjimConfig::LoadLUA()
    {
        int status;
        aether::lua::LuaState L;
        status = L.LoadFile("assets/enerjim/boot.lua");

        mStartingMapPath = L.GetGlobalString("startingMap", status);

        // load vania jumper config
        mVaniaJumperAgentConfig.jumpForce = L.GetGlobalFloat("jumpForce", status);
        mVaniaJumperAgentConfig.walkSpeed = L.GetGlobalFloat("walkSpeed", status);
        mVaniaJumperAgentConfig.coyoteTime = L.GetGlobalFloat("coyoteTime", status);
        mVaniaJumperAgentConfig.numberOfJumps = L.GetGlobalInt("numberOfJumps", status);

        // load gravity config
        mGravityConfig.fallingVelocityCap = L.GetGlobalFloat("fallingCap", status);
        mGravityConfig.gravityFactor = L.GetGlobalFloat("gravityFactor", status);
    }

}
