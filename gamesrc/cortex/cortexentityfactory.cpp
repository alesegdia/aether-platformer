#include "cortexentityfactory.h"


namespace cortex {

CortexEntityFactory::CortexEntityFactory(secs::Engine &world, int playerIndex)
    : BaseEntityFactory(world),
      m_playerIndex(playerIndex)
{
    aether::graphics::AsepriteAnimationLoader animloader;
    m_playerAnim = animloader.load("assets/sampleanim.json");
}

secs::Entity CortexEntityFactory::makePlayer(float x, float y)
{
    secs::Entity player = world().processor().addEntity();

    addBasicTilemapEntity(player, x, y, 58, 230);

    auto& render_comp = addComponent<RenderComponent>(player);
    render_comp.render_offset.set(0, 0); //-(256)/2.0f, -256/2.0f);
    render_comp.renderOrder = m_playerIndex;

    auto& animation_comp = addComponent<AnimationComponent>(player);
    animation_comp.animation = m_playerAnim.anims["anim1"].get();
    render_comp.texture = m_playerAnim.sheet->getFrame(0);

    addComponent<PlayerComponent>(player);
    
    auto& aic = addComponent<AgentInputComponent>(player);
    aic.horizontal_speed = Config::instance().playerSpeed;
    aic.jump_force = Config::instance().playerJumpForce;
    
    addComponent<JumperAgentComponent>(player);
    auto& atrc = addComponent<AnimatorComponent>(player);
    atrc.groundStandAnimation = m_playerAnim.anims["anim1"].get();
    atrc.groundWalkAnimation = m_playerAnim.anims["anim2"].get();
    atrc.airAnimation = m_playerAnim.anims["anim3"].get();

    auto& gc = addComponent<GravityComponent>(player);
    gc.gravityFactor = Config::instance().playerGravityFactor;
    gc.fallingVelocityCap = Config::instance().playerFallingCap;

    return player;
}

secs::Entity CortexEntityFactory::makeDoor( const Door::Shared& door )
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

}
