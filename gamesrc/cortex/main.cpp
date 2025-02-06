

#include "cortexapp.h"

#include "cortex/cortexconfig.h"


int main( int argc, char** argv )
{
    return cortex::createApp(cortex::CortexConfig::instance().windowWidth,
                             cortex::CortexConfig::instance().windowHeight)
            ->Exec(aether::core::CommandLineArguments(argc, argv));
}
