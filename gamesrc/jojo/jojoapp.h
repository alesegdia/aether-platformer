#include <aether/aether.h>


namespace jojo {

std::shared_ptr<aether::core::Application> createApp(int ww, int wh);

class JojoApp : public aether::core::Application
{
public:
    JojoApp(int w, int h);

    int ready(int argc, char **argv) override;

    void update(uint64_t delta) override;

    void dispose() override;

    int level = 1;
};



}

