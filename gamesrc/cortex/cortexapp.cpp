
#include "cortexapp.h"
#include <Tmx.h.in>

#include "cortex/screens/gameplayscreen.h"


namespace cortex {



std::shared_ptr<aether::core::Application> createApp(int ww, int wh)
{
    return std::make_shared<CortexApp>(ww, wh);
}


CortexApp::CortexApp(int w, int h)
    : aether::core::Application(w, h)
{

}

int CortexApp::Ready(const aether::core::CommandLineArguments& args)
{
    auto screen = std::static_pointer_cast<aether::core::IScreen>(std::make_shared<cortex::GameplayScreen>());
    SetScreen(screen);
    return 0;
}

void CortexApp::Update(uint64_t delta)
{
    aether::core::Application::Update(delta);
    if( aether::core::is_key_down(aether::core::KeyCode::Escape) )
    {
        Close();
    }
}

void CortexApp::Dispose()
{

}


}
