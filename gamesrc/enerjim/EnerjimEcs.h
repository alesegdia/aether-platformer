#pragma once


#include "aether/plugin/platformer/ecs/ecsworld.h"

#include <memory>


class AIAgentDumbWalkerSystem;

class CrazyAgentConfigurationData;

namespace enerjim {

class EnerjimECS : public ECSWorld
{
public:
    EnerjimECS();

	void SetTilemapMovementSolver(const std::shared_ptr<aether::tilemap::TilemapMovementSolver>& tilemapMovementSolver) override;

private:
    std::shared_ptr<AIAgentDumbWalkerSystem> m_aiAgentDumbWalkerSystem;

};


}
