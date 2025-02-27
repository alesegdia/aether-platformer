#include <aether/aether.h>

namespace enerjim {

std::shared_ptr<aether::core::Application> createApp(int ww, int wh);

class EnerjimApp : public aether::core::Application
{
public:
    EnerjimApp(int w, int h);

    std::vector<std::string> GetAssetPaths() const override
    {
        return { "media/", "assets/" };
    }

protected:
    int Ready(const aether::core::CommandLineArguments& args) override;

    void Update(uint64_t delta) override;

    void Dispose() override;

    int level = 1;
};



}

