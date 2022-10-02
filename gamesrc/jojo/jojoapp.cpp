
#include "jojoapp.h"
#include <Tmx.h.in>

#include "jojo/screens/gameplayscreen.h"


namespace jojo {



std::shared_ptr<aether::core::Application> createApp(int ww, int wh)
{
    return std::make_shared<JojoApp>(ww, wh);
}


JojoApp::JojoApp(int w, int h)
    : aether::core::Application(w, h)
{

}

int JojoApp::Ready(int argc, char **argv)
{
    auto screen = std::static_pointer_cast<aether::core::IScreen>(std::make_shared<jojo::GameplayScreen>());
    SetScreen(screen);
    return 0;
}

void JojoApp::Update(uint64_t delta)
{
    aether::core::Application::Update(delta);
    if( aether::core::is_key_down(aether::core::KeyCode::Escape) )
    {
        Close();
    }
}

void JojoApp::Dispose()
{

}


}
