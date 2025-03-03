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
        LoadLUA();
    }

    void EnerjimConfig::LoadLUA()
    {
        int status;
        aether::lua::LuaState L;
        status = L.LoadFile("assets/enerjim/boot.lua");

		mWindowWidth = L.GetGlobalFloat("windowWidth", status);
		mWindowHeight = L.GetGlobalFloat("windowHeight", status);
		mOrthoScale = L.GetGlobalFloat("orthoScale", status);

        // load vania jumper config
        mVaniaJumperAgentConfig.jumpForce = L.GetGlobalFloat("jumpForce", status);
        mVaniaJumperAgentConfig.walkSpeed = L.GetGlobalFloat("walkSpeed", status);
        mVaniaJumperAgentConfig.coyoteTime = L.GetGlobalFloat("coyoteTime", status);
        mVaniaJumperAgentConfig.numberOfJumps = L.GetGlobalInt("numberOfJumps", status);

        // load gravity config
        mGravityConfig.fallingVelocityCap = L.GetGlobalFloat("fallingCap", status);
        mGravityConfig.gravityFactor = L.GetGlobalFloat("gravityFactor", status);


        mStartingMapPath = L.GetGlobalString("startingMap", status);
    }

}
