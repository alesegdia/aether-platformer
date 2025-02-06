

#include "jojoapp.h"

#include "jojoconfig.h"


int main( int argc, char** argv )
{
    return jojo::createApp(jojo::JojoConfig::instance().windowWidth,
                    jojo::JojoConfig::instance().windowHeight)
            ->Exec(aether::core::CommandLineArguments(argc, argv));
}
