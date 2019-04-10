#pragma once

#include <aether/aether.h>

#include <TmxColor.h>

class RoomLayoutGameWorld;


namespace jojo {

class JojoWorld;

class GameplayScreen : public aether::core::IScreen
{
public:
    GameplayScreen();

    void show() final;
    void hide() final;
    void render() final;
    void update(uint64_t delta) final;

private:
    std::shared_ptr<JojoWorld> m_gameWorld;

};


}
