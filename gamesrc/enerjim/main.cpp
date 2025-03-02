

#include "EnerjimApp.h"

#include "EnerjimConfig.h"


int main( int argc, char** argv )
{
    return enerjim::createApp(enerjim::EnerjimConfig::instance().GetWindowWidth(),
                    enerjim::EnerjimConfig::instance().GetWindowHeight())
            ->Exec(aether::core::CommandLineArguments(argc, argv));
}
