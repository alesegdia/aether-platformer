

#include "platformerjam.h"

#include "constants.h"


int main( int argc, char** argv )
{
    PlatformerJam(Config::instance().windowWidth, Config::instance().windowHeight).exec(argc, argv);
}
