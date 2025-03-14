

#include "##GAMENAME##App.h"

#include "##GAMENAME##Config.h"


int main( int argc, char** argv )
{
    return ##GAMENAME##::createApp(##GAMENAME##::##GAMENAME##Config::instance().GetWindowWidth(),
                                   ##GAMENAME##::##GAMENAME##Config::instance().GetWindowHeight())
            ->Exec(aether::core::CommandLineArguments(argc, argv));
}
