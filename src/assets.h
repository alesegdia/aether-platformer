#pragma once

#include <aether/aether.h>

#include <TmxMap.h>


class Assets
{
public:
    void load()
    {
        font.load("assets/Alkhemikal.ttf", 16);
        playerTexture.load("assets/character-placeholder.png");
        playerSheet.load(1, 1, playerTexture);
        playerStandAnim.addFrame(playerSheet.getFrame(0));
        playerWalkAnim.addFrame(playerSheet.getFrame(0));
        playerAirAnim.addFrame(playerSheet.getFrame(0));

        leMap.ParseFile("assets/untitled.tmx");
    }

    void cleanup()
    {
        font.destroy();
        tilesetTexture.destroy();
    }

    aether::graphics::Font font;
    aether::graphics::Texture tilesetTexture;
    aether::graphics::Texture playerTexture;
    aether::graphics::Spritesheet tilesetSheet;
    aether::graphics::Spritesheet playerSheet;
    aether::graphics::Animation playerStandAnim;
    aether::graphics::Animation playerWalkAnim;
    aether::graphics::Animation playerAirAnim;
    Tmx::Map leMap;

};
