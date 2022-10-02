#include <aether/aether.h>


namespace cortex {

std::shared_ptr<aether::core::Application> createApp(int ww, int wh);

class CortexApp : public aether::core::Application
{
public:
    CortexApp(int w, int h);

    int Ready(int argc, char **argv) override;

    void Update(uint64_t delta) override;

    void Dispose() override;

    int level = 1;
};



}

