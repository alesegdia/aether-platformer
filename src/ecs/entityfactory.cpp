#include "entityfactory.h"

EntityFactory::EntityFactory(secs::Engine &ecsEngine)
    : m_ecsEngine(ecsEngine)
{

}

EntityFactory::~EntityFactory()
{

}

secs::Engine& EntityFactory::world()
{
    return m_ecsEngine;
}

DemuxEntityFactory::DemuxEntityFactory(secs::Engine &world, std::shared_ptr<Assets> assets)
    : EntityFactory(world),
      m_assets(assets)
{

}


secs::Entity DemuxEntityFactory::makePlayer(float x, float y)
{
    secs::Entity player = world().processor().addEntity();

    addBasicTilemapEntity(player, x, y, 200, 200);

    auto& render_comp = addComponent<RenderComponent>(player);
    render_comp.render_offset.set(0, 0);
    render_comp.texture = m_assets->playerSheet.getFrame(0);
    render_comp.render_offset.set(-5, -8);
    render_comp.renderOrder = 1;

    auto& animation_comp = addComponent<AnimationComponent>(player);
    animation_comp.animation = &m_assets->playerWalkAnim;

    addComponent<PlayerComponent>(player);
    addComponent<AgentInputComponent>(player);
    addComponent<JumperAgentComponent>(player);
    auto& atrc = addComponent<AnimatorComponent>(player);
    atrc.groundStandAnimation = &m_assets->playerStandAnim;
    atrc.groundWalkAnimation = &m_assets->playerWalkAnim;
    atrc.airAnimation = &m_assets->playerAirAnim;

    auto& gc = addComponent<GravityComponent>(player);
    gc.gravityFactor = 0.05f;
    gc.fallingVelocityCap = 2.f;

    return player;
}



