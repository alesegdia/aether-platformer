#include <aether/aether.h>


namespace ##PROJNAMELOWER## {

std::shared_ptr<aether::core::Application> createApp(int ww, int wh);

class ##PROJNAME##App : public aether::core::Application
{
public:
    ##PROJNAME##App(int w, int h);

    int ready(int argc, char **argv) override;

    void update(uint64_t delta) override;

    void dispose() override;

    int level = 1;
};



}

