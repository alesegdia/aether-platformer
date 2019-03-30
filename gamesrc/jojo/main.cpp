

#include "jojoapp.h"

#include "config.h"


int main( int argc, char** argv )
{
    jojo::createApp(Config::instance().windowWidth, Config::instance().windowHeight)->exec(argc, argv);
}
