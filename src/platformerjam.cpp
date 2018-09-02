
#include "platformerjam.h"

PlatformerJam::PlatformerJam(int w, int h)
    : aether::core::Application(w, h),
      gameplayScreen(this)
{

}

int PlatformerJam::ready(int argc, char **argv)
{
    assets.load();
    setScreen(&gameplayScreen);
    return 0;
}

void PlatformerJam::update(uint64_t delta)
{
    aether::core::Application::update(delta);
    if( aether::core::is_key_down(aether::core::KeyCode::Escape) )
    {
        close();
    }
}

void PlatformerJam::dispose()
{
    assets.cleanup();
}
