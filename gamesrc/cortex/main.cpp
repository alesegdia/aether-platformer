

#include "cortexapp.h"

#include "cortex/cortexconfig.h"


int main( int argc, char** argv )
{
    cortex::createApp(cortex::CortexConfig::instance().windowWidth,
                      cortex::CortexConfig::instance().windowHeight)
            ->exec(argc, argv);
}
