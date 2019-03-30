
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

int JojoApp::ready(int argc, char **argv)
{
    auto screen = std::static_pointer_cast<aether::core::IScreen>(std::make_shared<jojo::GameplayScreen>());
    setScreen(screen);
    return 0;
}

void JojoApp::update(uint64_t delta)
{
    aether::core::Application::update(delta);
    if( aether::core::is_key_down(aether::core::KeyCode::Escape) )
    {
        close();
    }
}

void JojoApp::dispose()
{

}


}
