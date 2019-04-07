#pragma once


#include "ecs/ecsworld.h"

#include <memory>


class AIAgentDumbWalkerSystem;


namespace jojo {

class JojoECS : public ECSWorld
{
public:
    JojoECS();

    void setCollisionTilemap(std::shared_ptr<aether::tilemap::CollisionTilemap> ct) override;

private:
    std::shared_ptr<AIAgentDumbWalkerSystem> m_aiAgentDumbWalkerSystem;

};


}
