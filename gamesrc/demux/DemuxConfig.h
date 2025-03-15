#pragma once


namespace Demux {

class DemuxConfig
{
public:
    static const DemuxConfig& instance();

	int GetWindowWidth() const;
    int GetWindowHeight() const;
    int GetOrthoScale() const;

private:
    DemuxConfig();

    void LoadLUA();

    int mWindowWidth;
    int mWindowHeight;
    int mOrthoScale;

};


}
