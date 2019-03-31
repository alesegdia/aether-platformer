#include "jojoentityfactory.h"
#include "jojoconfig.h"

namespace jojo {

JojoEntityFactory::JojoEntityFactory(secs::Engine &world, int playerIndex)
    : BaseEntityFactory(world),
      m_playerIndex(playerIndex)
{
    aether::graphics::AsepriteAnimationLoader animloader;
    m_playerAnim = animloader.load("assets/jojo/bicho.json");
}

secs::Entity JojoEntityFactory::makePlayer(float x, float y)
{
    secs::Entity player = world().processor().addEntity();

    addBasicTilemapEntity(player, x, y, 20, 20);

    auto& render_comp = addComponent<RenderComponent>(player);
    render_comp.render_offset.set(0, 0); //-(256)/2.0f, -256/2.0f);
    render_comp.renderOrder = m_playerIndex;

    auto& animation_comp = addComponent<AnimationComponent>(player);
    animation_comp.animation = m_playerAnim.anims["stand"].get();
    render_comp.texture = m_playerAnim.sheet->getFrame(0);

    addComponent<PlayerComponent>(player);
    
    auto& aic = addComponent<AgentInputComponent>(player);
    aic.horizontal_speed = jojo::JojoConfig::instance().playerSpeed;
    aic.jump_force = jojo::JojoConfig::instance().playerJumpForce;
    
    addComponent<JumperAgentComponent>(player);
    auto& atrc = addComponent<AnimatorComponent>(player);
    atrc.groundStandAnimation = m_playerAnim.anims["stand"].get();
    atrc.groundWalkAnimation = m_playerAnim.anims["walk"].get();
    atrc.airAnimation = m_playerAnim.anims["stand"].get();

    auto& gc = addComponent<GravityComponent>(player);
    gc.gravityFactor = jojo::JojoConfig::instance().playerGravityFactor;
    gc.fallingVelocityCap = jojo::JojoConfig::instance().playerFallingCap;

    return player;
}


}
