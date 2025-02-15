#include "jojoworld.h"
#include "jojoecs.h"
#include "jojofactory.h"
#include "jojoconfig.h"

#include "aether/lua/lua.h"

namespace jojo {

	int JojoWorld::Init()
	{
		Tmx::Map map;
		int retcode = LoadMapFromLua(map);
		if (retcode != 0)
		{
			return retcode;
		}

		// load tilemap
		m_tilemap = aether::tilemap::BuildMap(map);

		// get useful information
		auto playerIndex = m_tilemap->GetObjectLayer("player")->GetDepthOrder();
		auto collisionLayer = m_tilemap->GetTileLayer("collision");
		auto collisionTilemap = std::make_shared<aether::tilemap::AetherTilemapCollisionQueryInterface>(collisionLayer);
		auto collisionTilemapSolver = std::make_shared<aether::tilemap::TilemapMovementSolver>(collisionTilemap);
		collisionTilemap->SetInvertedY(true);
		collisionTilemapSolver->SetOneWayUp(true);

		// creation
		m_ecsWorld = std::make_shared<JojoECS>(/*m_tilemap->GetTotalHeightInPixels()*/);
		m_ecsWorld->SetTilemapMovementSolver(collisionTilemapSolver);
		m_factory = std::make_shared<JojoFactory>(m_ecsWorld->engine(), playerIndex);
		//m_playerEntity = m_factory->makePlayerFreeMover(100, 250);
		m_playerEntity = m_factory->makePlayer(100, 250);

		auto tilemapNode = aether::GEngine->CreateTilemapNode(m_tilemap);

		m_tilemap->GetObjectLayer("enemies")->ForEachObject([this](const auto& o) {
			const auto& type = o.props.at("type");
			auto x = o.aabb.center().GetX();
			auto y = o.aabb.center().GetY();
			if (type == "dumbwalker") {
				m_factory->makeBallEnemy(x, y - 4);
			}
		});

		auto viewport = aether::math::Vec2f {
				float(JojoConfig::instance().windowWidth),
				float(JojoConfig::instance().windowHeight) };
		auto cam = aether::GEngine->GetCamera(aether::render::CameraFlags::Default);
		cam->SetOrthographicSize(12.f);
		cam->SetPosition(100.f, 100.f, -100.f);

		m_platformerScroll = std::make_shared<aether::render::PlatformerScroller>(
					cam, aether::math::Rectf(0, 0, m_tilemap->GetTotalWidthInPixels(), m_tilemap->GetTotalHeightInPixels()),
					aether::math::Vec2f(800, 500));

		m_topDownScroll = std::make_shared<aether::render::TopDownMapScroller>();
		m_topDownScroll->Setup(cam, {{ -1000000, -1000000 }, { 100000000, 100000000 }});

		m_directScroller = std::make_shared<aether::render::DirectScroller>(cam);
		
		return 0;
	}

	int JojoWorld::LoadMapFromLua(Tmx::Map& map)
	{
		lua_State* L = luaL_newstate();
		luaL_openlibs(L);

		if (luaL_dofile(L, "assets/jojo/boot.lua") == LUA_OK)
		{
			lua_pop(L, lua_gettop(L));
		}
		else
		{
			return -1;
		}

		lua_getglobal(L, "startingMap");

		if (lua_isstring(L, -1))
		{
			const char* startingMap = lua_tostring(L, -1);
			lua_pop(L, 1);
			printf("Loading map: %s\n", startingMap);
			map.ParseFile(startingMap);
		}
		else
		{
			return -1;
		}


		lua_close(L);

	}

	void JojoWorld::Render()
	{
		auto& pos = m_ecsWorld->engine().GetComponent<TransformComponent>(m_playerEntity).position;

		// m_platformerScroll->Focus(pos.GetX(), pos.GetY());
		m_ecsWorld->render();

	}

	void JojoWorld::DebugTilemap()
	{
		auto zOffset = 100;
		auto collisionLayer = m_tilemap->GetTileLayer("collision");
		for (int i = 0; i < m_tilemap->GetWidthInTiles(); i++)
		{
			for (int j = 0; j < m_tilemap->GetHeightInTiles(); j++)
			{
				auto collisionBehaviour = collisionLayer->GetTileCollisionBehaviour(i, m_tilemap->GetHeightInTiles() - j - 1);
				if(collisionBehaviour == aether::tilemap::TileCollisionBehaviour::Solid)
				{
					float size = 16;
					// draw AABB for tile
					aether::GEngine->GetInstantRenderer()->DrawAABB({ {i * size, j * size, zOffset}, {(i+1) * size, (j+1) * size, zOffset + 10} }, aether::render::Color::Red);

					//aether::GEngine->GetInstantRenderer()->DrawAABB({ {}, {} }, aether::render::Color::Blue);
				}
			}
		}

		auto aabb = m_ecsWorld->engine().GetComponent<AABBComponent>(m_playerEntity).aabb;


		aether::GEngine->GetInstantRenderer()->DrawAABB({ {aabb.x1(), aabb.y1(), 0}, {aabb.x2(), aabb.y2(), 100.f}}, aether::render::Color::Green, -1);

	}


	void JojoWorld::Update(double delta)
	{
		m_ecsWorld->step(delta);
		auto& pc = m_ecsWorld->engine().GetComponent<TransformComponent>(m_playerEntity);
		auto& tc = m_ecsWorld->engine().GetComponent<TilemapCollisionComponent>(m_playerEntity);
		auto& aabb = m_ecsWorld->engine().GetComponent<AABBComponent>(m_playerEntity);

		/*
		m_platformerScroll->Update(delta);

		m_platformerScroll->SetSnapToPlatform(tc.lastCollisionInfo.y_collision_direction == 1);

		if( tc.lastCollisionInfo.y_collision_direction == 1 )
		{
			m_platformerScroll->SnapToPlatform(pc.position.GetY());
		}
		*/

		m_directScroller->Focus(aabb.aabb.x() + aabb.aabb.w() / 2.f, aabb.aabb.y() + aabb.aabb.h() / 2.f);
		//m_topDownScroll->Focus(pc.position.GetX(), pc.position.GetY());
	}

	const secs::Engine& JojoWorld::GetECSWorld() const
	{
		return m_ecsWorld->engine();
	}

}
