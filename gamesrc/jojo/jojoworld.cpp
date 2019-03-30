#include "jojoworld.h"
#include "jojoecs.h"
#include "jojoentityfactory.h"

namespace jojo {

JojoWorld::JojoWorld()
{
    // load tilemap
    Tmx::Map map;
    map.ParseFile("assets/jojo/levels/level1.tmx");
    m_tilemap = aether::tilemap::buildMap(map);

    // get useful information
    auto playerIndex = m_tilemap->getObjectLayer("player")->zOrder();
    auto collisionLayer = m_tilemap->getTileLayer("collision");
    auto collisionTilemap = std::make_shared<aether::tilemap::CollisionTilemap>(collisionLayer);

    // creation
    m_ecsWorld = std::make_shared<JojoECS>();
    m_ecsWorld->setCollisionTilemap(collisionTilemap);
    m_factory = std::make_shared<JojoEntityFactory>(m_ecsWorld->engine(), playerIndex);
    m_playerEntity = m_factory->makePlayer(100, 100);
}

void JojoWorld::render()
{
    auto pos = m_ecsWorld->engine().component<TransformComponent>(m_playerEntity).position;

    ALLEGRO_TRANSFORM tr;
    al_identity_transform(&tr);
    al_build_transform(&tr, (Config::instance().windowWidth / 2) - pos.x(), (Config::instance().windowHeight / 2) - pos.y(), 1.0f, 1.0f, 0);
    al_use_transform(&tr);

    m_ecsWorld->render();
}


void JojoWorld::update(double delta)
{
    m_ecsWorld->step(delta);
}


}
