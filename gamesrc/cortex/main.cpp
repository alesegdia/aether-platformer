

#include "cortexapp.h"

#include "constants.h"


int main( int argc, char** argv )
{
    cortex::createApp(Config::instance().windowWidth, Config::instance().windowHeight)->exec(argc, argv);
}
