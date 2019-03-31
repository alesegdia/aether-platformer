#include "jojoworld.h"
#include "jojoecs.h"
#include "jojoentityfactory.h"
#include "jojoconfig.h"


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

    // create layers
    for( auto& layer : m_tilemap->getTileLayers() )
    {
        auto layerEntity = m_ecsWorld->engine().processor().addEntity();
        auto& renderComponent = m_ecsWorld->engine().processor().addComponent<RenderComponent>(layerEntity);
        renderComponent.layer = layer.second;
        renderComponent.renderOrder = layer.second->zOrder();
        m_ecsWorld->engine().processor().addComponent<TransformComponent>(layerEntity).position.set(0, 0);
    }
}

void JojoWorld::render()
{
    auto pos = m_ecsWorld->engine().component<TransformComponent>(m_playerEntity).position;

    ALLEGRO_TRANSFORM tr;
    al_identity_transform(&tr);
    al_build_transform(&tr,
                       (jojo::JojoConfig::instance().windowWidth / 2) - pos.x() * 4,
                       (jojo::JojoConfig::instance().windowHeight / 2) - pos.y() * 4,
                       4.0f, 4.0f, 0);
    al_use_transform(&tr);

    m_ecsWorld->render();
}


void JojoWorld::update(double delta)
{
    m_ecsWorld->step(delta);
}


}
