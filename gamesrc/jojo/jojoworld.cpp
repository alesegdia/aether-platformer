#include "jojoworld.h"
#include "jojoecs.h"
#include "jojofactory.h"
#include "jojoconfig.h"

#include "aether/lua/lua.h"

namespace jojo {

JojoWorld::JojoWorld()
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    if (luaL_dofile(L, "assets/jojo/boot.lua") == LUA_OK)
    {
        lua_pop(L, lua_gettop(L));
    }

    lua_getglobal(L, "startingMap");

    if (lua_isstring(L, -1))
    {
        const char* startingMap = lua_tostring(L, -1);
        lua_pop(L, 1);
        printf("Loading map: %s\n", startingMap);
    }

    lua_close(L);

    // load tilemap
    Tmx::Map map;
    map.ParseFile("assets/jojo/levels/level1.tmx");
    m_tilemap = aether::tilemap::BuildMap(map);

    // get useful information
    auto playerIndex = m_tilemap->GetObjectLayer("player")->GetDepthOrder();
    auto collisionLayer = m_tilemap->GetTileLayer("collision");
    auto collisionTilemap = std::make_shared<aether::tilemap::CollisionTilemap>(collisionLayer);

    // creation
    m_ecsWorld = std::make_shared<JojoECS>();
    m_ecsWorld->setCollisionTilemap(collisionTilemap);
    m_factory = std::make_shared<JojoFactory>(m_ecsWorld->engine(), playerIndex);
    m_playerEntity = m_factory->makePlayer(100, 250);

    // create layers
    for( auto& layer : m_tilemap->GetTileLayers() )
    {
        auto layerEntity = m_ecsWorld->engine().GetEntityProcessor().AddEntity();
        auto& renderComponent = m_ecsWorld->engine().GetEntityProcessor().AddComponent<RenderComponent>(layerEntity);
        renderComponent.layer = layer.second;
        renderComponent.renderOrder = layer.second->GetDepthOrder();
        m_ecsWorld->engine().GetEntityProcessor().AddComponent<TransformComponent>(layerEntity).position.Set(0, 0);
    }

    m_tilemap->GetObjectLayer("enemies")->ForEachObject([this](const auto& o) {
        const auto& type = o.props.at("type");
        auto x = o.aabb.center().GetX();
        auto y = o.aabb.center().GetY();
        if( type == "dumbwalker" ) {
            m_factory->makeBallEnemy(x, y-4);
        }
    });

    auto viewport = aether::math::Vec2f{
            float(JojoConfig::instance().windowWidth),
            float(JojoConfig::instance().windowHeight)};
    m_cam = std::make_shared<aether::graphics::Camera>(viewport);
    m_cam->SetScale(8.f, 8.f);

    m_scroll = std::make_shared<aether::graphics::PlatformerScroller>(
                m_cam, aether::math::Rectf(0, 0, m_tilemap->GetWidth(), m_tilemap->GetHeight()),
                aether::math::Vec2f(800, 500));

}

void JojoWorld::render()
{
    auto pos = m_ecsWorld->engine().GetComponent<TransformComponent>(m_playerEntity).position;

    m_scroll->Focus(pos.GetX(), pos.GetY());
    m_ecsWorld->render();
}


void JojoWorld::update(double delta)
{
    m_ecsWorld->step(delta);
    auto& pc = m_ecsWorld->engine().GetComponent<TransformComponent>(m_playerEntity);
    auto& tc = m_ecsWorld->engine().GetComponent<TilemapCollisionComponent>(m_playerEntity);

    m_scroll->Update(delta);

    m_scroll->SetSnapToPlatform(tc.lastCollisionInfo.y_collision_direction == 1);

    if( tc.lastCollisionInfo.y_collision_direction == 1 )
    {
        m_scroll->SnapToPlatform(pc.position.GetY());
    }
}


}
