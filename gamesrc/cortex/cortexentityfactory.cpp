#include "cortexentityfactory.h"
#include "cortexconfig.h"

namespace cortex {

CortexEntityFactory::CortexEntityFactory(secs::Engine &world, int playerIndex)
    : BaseEntityFactory(world),
      m_playerIndex(playerIndex)
{
    aether::render::AsepriteAnimationLoader animloader;
    m_playerAnim = animloader.Load("assets/sampleanim.json");
}

secs::Entity CortexEntityFactory::makePlayer(float x, float y)
{
    secs::Entity player = world().GetEntityProcessor().AddEntity();

    addBasicTilemapEntity(player, x, y, 58, 230);

    auto& render_comp = addComponent<RenderComponent>(player);
    render_comp.sprite = aether::GEngine->CreateSpriteNode(glm::fvec2{ 32, 32 });
    render_comp.sprite->LoadAllAnimations(m_playerAnim);
    render_comp.sprite->PlayAnimation("anim1");
    render_comp.currentAnimation = "anim1";

    addComponent<PlayerComponent>(player);
    
    auto& aic = addComponent<AgentInputComponent>(player);
    aic.horizontal_speed = cortex::CortexConfig::instance().playerSpeed;
    aic.jump_force = cortex::CortexConfig::instance().playerJumpForce;
    
    addComponent<JumperAgentComponent>(player);
    auto& atrc = addComponent<AnimatorComponent>(player);
    atrc.groundStandAnimation = "anim1";
    atrc.groundWalkAnimation = "anim2";
    atrc.airAnimation = "anim3";

    auto& gc = addComponent<GravityComponent>(player);
    gc.gravityFactor = cortex::CortexConfig::instance().playerGravityFactor;
    gc.fallingVelocityCap = cortex::CortexConfig::instance().playerFallingCap;

    return player;
}

secs::Entity CortexEntityFactory::makeDoor( const Door::Shared& door )
{
    secs::Entity e = world().GetEntityProcessor().AddEntity();
    
    auto x = float(door->getRect().x());
    auto y = float(door->getRect().y());
    auto w = float(door->getRect().w());
    auto h = float(door->getRect().h());
    
    auto& tc = addComponent<TransformComponent>(e);
    tc.position.Set(x, y);
    
    auto& dc = addComponent<DoorComponent>(e);
    dc.door = door;
    
    auto& aabb_comp = addComponent<AABBComponent>(e);
    aabb_comp.aabb = aether::math::Recti(x, y, w, h);
    
    auto& hcc = addComponent<HadronCollisionComponent>(e);
    hcc.body = new hadron::Body(x, y, w, h);
    hcc.offset.Set(0, 0);

    return e;    
}

}
