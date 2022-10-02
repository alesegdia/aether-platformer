

#include "jojoapp.h"

#include "jojoconfig.h"


int main( int argc, char** argv )
{
    jojo::createApp(jojo::JojoConfig::instance().windowWidth,
                    jojo::JojoConfig::instance().windowHeight)
            ->Exec(argc, argv);
}
