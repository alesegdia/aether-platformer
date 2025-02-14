#pragma once


#include "aether/plugin/platformer/ecs/ecsworld.h"

#include <memory>


class AIAgentDumbWalkerSystem;


namespace jojo {

class JojoECS : public ECSWorld
{
public:
    JojoECS();

	void SetTilemapMovementSolver(const std::shared_ptr<aether::tilemap::TilemapMovementSolver>& tilemapMovementSolver) override;

private:
    std::shared_ptr<AIAgentDumbWalkerSystem> m_aiAgentDumbWalkerSystem;

};


}
