

#include "DemuxApp.h"

#include "DemuxConfig.h"


int main( int argc, char** argv )
{
    return Demux::createApp(Demux::DemuxConfig::instance().GetWindowWidth(),
                                   Demux::DemuxConfig::instance().GetWindowHeight())
            ->Exec(aether::core::CommandLineArguments(argc, argv));
}
