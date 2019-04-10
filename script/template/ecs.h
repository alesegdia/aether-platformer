#pragma once


#include "ecs/ecsworld.h"

#include <memory>


class AIAgentDumbWalkerSystem;


namespace ##PROJNAMELOWER## {

class ##PROJNAME##ECS : public ECSWorld
{
public:
    ##PROJNAME##ECS();

    void setCollisionTilemap(std::shared_ptr<aether::tilemap::CollisionTilemap> ct) override;

private:
    std::shared_ptr<AIAgentDumbWalkerSystem> m_aiAgentDumbWalkerSystem;

};


}
