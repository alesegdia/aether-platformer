

#include "EnerjimApp.h"

#include "EnerjimConfig.h"


int main( int argc, char** argv )
{
    return enerjim::createApp(enerjim::EnerjimConfig::instance().windowWidth,
                    enerjim::EnerjimConfig::instance().windowHeight)
            ->Exec(aether::core::CommandLineArguments(argc, argv));
}
