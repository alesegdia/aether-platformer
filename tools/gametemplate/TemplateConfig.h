#pragma once


namespace ##GAMENAME## {

class ##GAMENAME##Config
{
public:
    static const ##GAMENAME##Config& instance();

	int GetWindowWidth() const;
    int GetWindowHeight() const;
    int GetOrthoScale() const;

private:
    ##GAMENAME##Config();

    void LoadLUA();

    int mWindowWidth;
    int mWindowHeight;
    int mOrthoScale;

};


}
