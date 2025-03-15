#include <aether/aether.h>

namespace Demux {

std::shared_ptr<aether::core::Application> createApp(int ww, int wh);

class DemuxApp : public aether::core::Application
{
public:
    DemuxApp(int w, int h);

    std::vector<std::string> GetAssetPaths() const override;

protected:
    int Ready(const aether::core::CommandLineArguments& args) override;
    void Update(uint64_t delta) override;
    void Dispose() override;

};



}

