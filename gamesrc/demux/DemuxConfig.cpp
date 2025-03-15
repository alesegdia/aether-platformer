#pragma once

#include "DemuxConfig.h"
#include "aether/lua/helpers.h"


namespace {

}

namespace Demux {

	const Demux::DemuxConfig& DemuxConfig::instance()
	{
		static DemuxConfig config;
		return config;
	}

	int DemuxConfig::GetWindowWidth() const
    {
        return mWindowWidth;
    }

    int DemuxConfig::GetWindowHeight() const
    {
        return mWindowHeight;
    }

    int DemuxConfig::GetOrthoScale() const
    {
        return mOrthoScale;
    }

	DemuxConfig::DemuxConfig()
    {
        LoadLUA();
    }

    void DemuxConfig::LoadLUA()
    {
        int status;
        aether::lua::LuaState L;
        status = L.LoadFile("assets/Demux/boot.lua");

		mWindowWidth = L.GetGlobalFloat("windowWidth", status);
		mWindowHeight = L.GetGlobalFloat("windowHeight", status);
		mOrthoScale = L.GetGlobalFloat("orthoScale", status);
    }

}
