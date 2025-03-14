#include <aether/aether.h>

namespace ##GAMENAME## {

std::shared_ptr<aether::core::Application> createApp(int ww, int wh);

class ##GAMENAME##App : public aether::core::Application
{
public:
    ##GAMENAME##App(int w, int h);

    std::vector<std::string> GetAssetPaths() const override;

protected:
    int Ready(const aether::core::CommandLineArguments& args) override;

    void Update(uint64_t delta) override;

    void Dispose() override;

    int level = 1;
};



}

