#pragma once


#include "aether/plugin/platformer/ecs/ecsworld.h"

#include <memory>


class AIAgentDumbWalkerSystem;

class CrazyAgentConfigurationData;

namespace jojo {

class JojoECS : public ECSWorld
{
public:
    JojoECS(const CrazyAgentConfigurationData& data);

	void SetTilemapMovementSolver(const std::shared_ptr<aether::tilemap::TilemapMovementSolver>& tilemapMovementSolver) override;

private:
    std::shared_ptr<AIAgentDumbWalkerSystem> m_aiAgentDumbWalkerSystem;

};


}
