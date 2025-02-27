
#include "EnerjimApp.h"
#include <Tmx.h.in>
#include "imgui.h"

#include "enerjim/screens/gameplayscreen.h"


namespace enerjim {


std::shared_ptr<aether::core::Application> createApp(int ww, int wh)
{
    return std::make_shared<EnerjimApp>(ww, wh);
}


EnerjimApp::EnerjimApp(int w, int h)
    : aether::core::Application(w, h)
{

}

int EnerjimApp::Ready(const aether::core::CommandLineArguments& args)
{
    auto screen = std::static_pointer_cast<aether::core::IScreen>(std::make_shared<enerjim::GameplayScreen>());
    SetScreen(screen);
    return 0;
}

void EnerjimApp::Update(uint64_t delta)
{
    aether::core::Application::Update(delta);
    if( aether::core::is_key_down(aether::core::KeyCode::Escape) )
    {
        Close();
    }
}

void EnerjimApp::Dispose()
{

}


}
