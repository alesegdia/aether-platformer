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

void EntityFactory::addBasicTilemapEntity(secs::Entity e, float x, float y, float w, float h, float dx, float dy)
{    auto& transform_comp = addComponent<TransformComponent>(e);    transform_comp.position.set( x, y );    transform_comp.position.set( x, y );
    //transform_comp.offset.set(dx, dy);    auto& aabb_comp = addComponent<AABBComponent>(e);    aabb_comp.aabb = aether::math::Recti(0, 0, w, h);
    auto& hcc = addComponent<HadronCollisionComponent>(e);    hcc.body = new hadron::Body(x, y, w, h);    hcc.offset.set(dx, dy);    addComponent<VelocityComponent>(e);    addComponent<TilemapCollisionComponent>(e);}

DemuxEntityFactory::DemuxEntityFactory(secs::Engine &world, std::shared_ptr<Assets> assets, int playerIndex)
    : EntityFactory(world),
      m_assets(assets),
      m_playerIndex(playerIndex)
{

}


secs::Entity DemuxEntityFactory::makePlayer(float x, float y)
{
    secs::Entity player = world().processor().addEntity();

    addBasicTilemapEntity(player, x, y, 58, 230, 0, 0);

    auto& render_comp = addComponent<RenderComponent>(player);
    render_comp.render_offset.set(-(256-58)/2.0f, -20);
    render_comp.texture = m_assets->playerSheet.getFrame(0);
    render_comp.renderOrder = m_playerIndex;

    auto& animation_comp = addComponent<AnimationComponent>(player);
    animation_comp.animation = &m_assets->playerWalkAnim;

    addComponent<PlayerComponent>(player);
    
    auto& aic = addComponent<AgentInputComponent>(player);
    aic.horizontal_speed = Config::instance().playerSpeed;
    aic.jump_force = Config::instance().playerJumpForce;
    
    addComponent<JumperAgentComponent>(player);
    auto& atrc = addComponent<AnimatorComponent>(player);
    atrc.groundStandAnimation = &m_assets->playerStandAnim;
    atrc.groundWalkAnimation = &m_assets->playerWalkAnim;
    atrc.airAnimation = &m_assets->playerAirAnim;

    auto& gc = addComponent<GravityComponent>(player);
    gc.gravityFactor = Config::instance().playerGravityFactor;
    gc.fallingVelocityCap = Config::instance().playerFallingCap;

    return player;
}

secs::Entity DemuxEntityFactory::makeDoor( const Door::Shared& door )
{
    secs::Entity e = world().processor().addEntity();
    
    auto x = float(door->getRect().x());
    auto y = float(door->getRect().y());
    auto w = float(door->getRect().w());
    auto h = float(door->getRect().h());
    
    auto& tc = addComponent<TransformComponent>(e);
    tc.position.set(x, y);
    
    auto& dc = addComponent<DoorComponent>(e);
    dc.door = door;
    
    auto& aabb_comp = addComponent<AABBComponent>(e);
    aabb_comp.aabb = aether::math::Recti(x, y, w, h);
    
    auto& hcc = addComponent<HadronCollisionComponent>(e);
    hcc.body = new hadron::Body(x, y, w, h);
    hcc.offset.set(0, 0);

    return e;    
}

