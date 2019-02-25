#include "entityfactory.h"

EntityFactory::EntityFactory(secs::Engine &world, Assets& assets)
    : m_world(world),
      m_assets(assets)
{

}

secs::Entity EntityFactory::makePlayer(float x, float y)
{
    secs::Entity player = m_world.processor().addEntity();

    auto& transform_comp = addComponent<TransformComponent>(player);
    transform_comp.position.set( x, y );
    transform_comp.position.set( x, y );

    auto& render_comp = addComponent<RenderComponent>(player);
    render_comp.render_offset.set(0, 0);
    render_comp.texture = m_assets.playerSheet.getFrame(0);
    render_comp.render_offset.set(-5, -8);
    render_comp.renderOrder = 1;

    auto& animation_comp = addComponent<AnimationComponent>(player);
    animation_comp.animation = &m_assets.playerWalkAnim;

    auto& aabb_comp = addComponent<AABBComponent>(player);
    aabb_comp.aabb = aether::math::Recti(0, 0, 200, 200);

    auto& hcc = addComponent<HadronCollisionComponent>(player);
    hcc.body = new hadron::Body(x, y, 200, 200);
    hcc.offset.set(0, 0);

    auto& vc = addComponent<VelocityComponent>(player);

    addComponent<PlayerComponent>(player);
    addComponent<AgentInputComponent>(player);
    addComponent<JumperAgentComponent>(player);
    auto& atrc = addComponent<AnimatorComponent>(player);
    atrc.groundStandAnimation = &m_assets.playerStandAnim;
    atrc.groundWalkAnimation = &m_assets.playerWalkAnim;
    atrc.airAnimation = &m_assets.playerAirAnim;

    addComponent<TilemapCollisionComponent>(player);
    auto& gc = addComponent<GravityComponent>(player);
    gc.gravityFactor = 0.05f;
    gc.fallingVelocityCap = 2.f;

    return player;
}


