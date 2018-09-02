#include <aether/aether.h>

#include "screens/gameplayscreen.h"
#include "assets.h"

class PlatformerJam : public aether::core::Application
{
public:
    PlatformerJam(int w, int h);

    int ready(int argc, char **argv) override;

    void update(uint64_t delta) override;

    void dispose() override;

    GameplayScreen gameplayScreen;

    Assets assets;

    int level = 1;
};

