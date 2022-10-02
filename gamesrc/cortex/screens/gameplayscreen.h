#pragma once

#include <aether/aether.h>

#include <TmxColor.h>

class RoomLayoutGameWorld;


namespace cortex {


class GameplayScreen : public aether::core::IScreen
{
public:
    GameplayScreen();

    int Load() final;
    int Unload() final;
    void Render() final;
    void Update(uint64_t delta) final;

private:
    std::shared_ptr<RoomLayoutGameWorld> m_gameWorld;

};


}
