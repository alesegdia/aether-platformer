

#include "##PROJNAMELOWER##app.h"

#include "##PROJNAMELOWER##config.h"


int main( int argc, char** argv )
{
    ##PROJNAMELOWER##::createApp(##PROJNAMELOWER##::##PROJNAME##Config::instance().windowWidth,
                    ##PROJNAMELOWER##::##PROJNAME##Config::instance().windowHeight)
            ->exec(argc, argv);
}
