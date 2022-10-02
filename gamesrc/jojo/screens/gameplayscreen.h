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

    int Load() final;
    int Unload() final;
    void Render() final;
    void Update(uint64_t delta) final;

private:
    std::shared_ptr<JojoWorld> m_gameWorld;

};


}
