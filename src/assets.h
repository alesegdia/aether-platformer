#pragma once

#include <aether/aether.h>

#include <TmxMap.h>


class Assets
{
public:
    void load()
    {
        font.load("assets/Alkhemikal.ttf", 16);
        tilesetTexture.load("assets/tileset.png");
        playerTexture.load("assets/playersheet.png");
        tilesetSheet.load(4, 2, tilesetTexture);
        playerSheet.load(3, 2, playerTexture);
        playerStandAnim.addFrame(playerSheet.getFrame(0));

        playerWalkAnim.addFrame(playerSheet.getFrame(0, 0));
        playerWalkAnim.addFrame(playerSheet.getFrame(0, 1));
        playerWalkAnim.addFrame(playerSheet.getFrame(1, 0));
        playerWalkAnim.addFrame(playerSheet.getFrame(0, 1));

        playerAirAnim.addFrame(playerSheet.getFrame(1, 1));
        playerAirAnim.addFrame(playerSheet.getFrame(2, 0));
        playerAirAnim.addFrame(playerSheet.getFrame(2, 1));

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
