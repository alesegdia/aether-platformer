#include "DemuxApp.h"
#include "Demux/screens/gameplayscreen.h"


namespace Demux {


std::shared_ptr<aether::core::Application> createApp(int ww, int wh)
{
    return std::make_shared<DemuxApp>(ww, wh);
}


DemuxApp::DemuxApp(int w, int h)
    : aether::core::Application(w, h)
{

}

std::vector<std::string> DemuxApp::GetAssetPaths() const
{
    return { "media/", "assets/" };
}

int DemuxApp::Ready(const aether::core::CommandLineArguments& args)
{
    auto screen = std::static_pointer_cast<aether::core::IScreen>(std::make_shared<Demux::GameplayScreen>());
    SetScreen(screen);
    return 0;
}

void DemuxApp::Update(uint64_t delta)
{
    aether::core::Application::Update(delta);
    if( aether::core::is_key_down(aether::core::KeyCode::Escape) )
    {
        Close();
    }
}

void DemuxApp::Dispose()
{

}


}
