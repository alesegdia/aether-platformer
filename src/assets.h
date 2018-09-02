#pragma once

#include <aether/aether.h>

class Assets
{
public:
    void load()
    {
        font.load("assets/Alkhemikal.ttf", 16);
    }

    void cleanup()
    {
        font.destroy();
    }

    aether::graphics::Font font;

};
