#include "##GAMENAME##App.h"
#include "##GAMENAME##/screens/gameplayscreen.h"


namespace ##GAMENAME## {


std::shared_ptr<aether::core::Application> createApp(int ww, int wh)
{
    return std::make_shared<##GAMENAME##App>(ww, wh);
}


##GAMENAME##App::##GAMENAME##App(int w, int h)
    : aether::core::Application(w, h)
{

}

std::vector<std::string> ##GAMENAME##App::GetAssetPaths() const
{
    return { "media/", "assets/" };
}

int ##GAMENAME##App::Ready(const aether::core::CommandLineArguments& args)
{
    auto screen = std::static_pointer_cast<aether::core::IScreen>(std::make_shared<##GAMENAME##::GameplayScreen>());
    SetScreen(screen);
    return 0;
}

void ##GAMENAME##App::Update(uint64_t delta)
{
    aether::core::Application::Update(delta);
    if( aether::core::is_key_down(aether::core::KeyCode::Escape) )
    {
        Close();
    }
}

void ##GAMENAME##App::Dispose()
{

}


}
