#include "jojoworld.h"
#include "jojoecs.h"
#include "jojofactory.h"
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
    m_factory = std::make_shared<JojoFactory>(m_ecsWorld->engine(), playerIndex);
    m_playerEntity = m_factory->makePlayer(100, 250);

    // create layers
    for( auto& layer : m_tilemap->getTileLayers() )
    {
        auto layerEntity = m_ecsWorld->engine().processor().addEntity();
        auto& renderComponent = m_ecsWorld->engine().processor().addComponent<RenderComponent>(layerEntity);
        renderComponent.layer = layer.second;
        renderComponent.renderOrder = layer.second->zOrder();
        m_ecsWorld->engine().processor().addComponent<TransformComponent>(layerEntity).position.set(0, 0);
    }

    m_tilemap->getObjectLayer("enemies")->foreach([this](const auto& o) {
        const auto& type = o.props.at("type");
        auto x = o.aabb.center().x();
        auto y = o.aabb.center().y();
        if( type == "dumbwalker" ) {
            m_factory->makeBallEnemy(x, y-4);
        }
    });

    auto viewport = aether::math::Vec2f{
            float(JojoConfig::instance().windowWidth),
            float(JojoConfig::instance().windowHeight)};
    m_cam = std::make_shared<aether::graphics::Camera>(viewport);
    m_cam->scale(8.f, 8.f);

    m_scroll = std::make_shared<aether::graphics::PlatformerScroller>(
                m_cam, aether::math::Rectf(0, 0, m_tilemap->width(), m_tilemap->height()),
                aether::math::Vec2f(800, 500));
}

void JojoWorld::render()
{
    auto pos = m_ecsWorld->engine().component<TransformComponent>(m_playerEntity).position;

    m_scroll->focus(pos.x(), pos.y());
    m_ecsWorld->render();
}


void JojoWorld::update(double delta)
{
    m_ecsWorld->step(delta);
    auto& pc = m_ecsWorld->engine().component<TransformComponent>(m_playerEntity);
    auto& tc = m_ecsWorld->engine().component<TilemapCollisionComponent>(m_playerEntity);

    m_scroll->update(delta);

    m_scroll->setSnapToPlatform(tc.lastCollisionInfo.y_collision_direction == 1);

    if( tc.lastCollisionInfo.y_collision_direction == 1 )
    {
        m_scroll->snapToPlatform(pc.position.y());
    }
}


}
