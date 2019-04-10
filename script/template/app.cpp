
#include "##PROJNAMELOWER##app.h"
#include <Tmx.h.in>

#include "##PROJNAMELOWER##/screens/gameplayscreen.h"


namespace ##PROJNAMELOWER## {



std::shared_ptr<aether::core::Application> createApp(int ww, int wh)
{
    return std::make_shared<##PROJNAME##App>(ww, wh);
}


##PROJNAME##App::##PROJNAME##App(int w, int h)
    : aether::core::Application(w, h)
{

}

int ##PROJNAME##App::ready(int argc, char **argv)
{
    auto screen = std::static_pointer_cast<aether::core::IScreen>(std::make_shared<jojo::GameplayScreen>());
    setScreen(screen);
    return 0;
}

void ##PROJNAME##App::update(uint64_t delta)
{
    aether::core::Application::update(delta);
    if( aether::core::is_key_down(aether::core::KeyCode::Escape) )
    {
        close();
    }
}

void ##PROJNAME##App::dispose()
{

}


}
