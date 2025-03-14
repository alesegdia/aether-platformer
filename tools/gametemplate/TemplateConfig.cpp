#pragma once

#include "##GAMENAME##Config.h"
#include "aether/lua/helpers.h"


namespace {

}

namespace ##GAMENAME## {

	const ##GAMENAME##::##GAMENAME##Config& ##GAMENAME##Config::instance()
	{
		static ##GAMENAME##Config config;
		return config;
	}

	int ##GAMENAME##Config::GetWindowWidth() const
    {
        return mWindowWidth;
    }

    int ##GAMENAME##Config::GetWindowHeight() const
    {
        return mWindowHeight;
    }

    int ##GAMENAME##Config::GetOrthoScale() const
    {
        return mOrthoScale;
    }

	const std::string& ##GAMENAME##Config::GetStartingMapPath() const
	{
		return mStartingMapPath;
	}

	##GAMENAME##Config::##GAMENAME##Config()
    {
        LoadLUA();
    }

    void ##GAMENAME##Config::LoadLUA()
    {
        int status;
        aether::lua::LuaState L;
        status = L.LoadFile("assets/##GAMENAME##/boot.lua");

		mWindowWidth = L.GetGlobalFloat("windowWidth", status);
		mWindowHeight = L.GetGlobalFloat("windowHeight", status);
		mOrthoScale = L.GetGlobalFloat("orthoScale", status);
        mStartingMapPath = L.GetGlobalString("startingMap", status);
    }

}
