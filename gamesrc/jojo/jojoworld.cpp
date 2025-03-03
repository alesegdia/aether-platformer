#include "jojoworld.h"
#include "jojoecs.h"
#include "jojofactory.h"
#include "jojoconfig.h"

#include "aether/lua/lua.h"

#include "aether/plugin/platformer/ecs/component/TransformComponent.h"
#include "aether/plugin/platformer/ecs/component/AABBComponent.h"
#include "aether/plugin/platformer/ecs/component/RenderComponent.h"
#include "aether/plugin/platformer/ecs/system/CrazyController/CrazyControllerSystem.h"

#include "aether/plugin/platformer/ecs/component/TilemapCollisionComponent.h"

#include "aether/lua/helpers.h"

namespace {
	


	std::shared_ptr<CrazyAgentConfigurationData> GetInitialCrazyAgentConfigurationDataFromLuaFile()
	{
		int status;
		aether::lua::LuaState L;
		status = L.LoadFile("assets/jojo/boot.lua");

		// load all the data with GetGlobalFloat in the temporary data
		std::shared_ptr<CrazyAgentConfigurationData> data = std::make_shared<CrazyAgentConfigurationData>();
		data->walkSpeed = L.GetGlobalFloat("walkSpeed", status);
		data->walkSpeedIncrement = L.GetGlobalFloat("walkSpeedIncrement", status);
		data->walkFriction = L.GetGlobalFloat("walkFriction", status);
		data->dashSpeed = L.GetGlobalFloat("dashSpeed", status);
		data->dashFriction = L.GetGlobalFloat("dashFriction", status);
		data->jumpForce = L.GetGlobalFloat("jumpForce", status);
		data->gravityFactor = L.GetGlobalFloat("gravityFactor", status);
		data->fallingCap = L.GetGlobalFloat("fallingCap", status);
		data->dashDuration = L.GetGlobalFloat("dashDuration", status);
		data->dashJumpForce = L.GetGlobalFloat("dashJumpForce", status);
		data->dashCooldown = L.GetGlobalFloat("dashCooldown", status);

		data->stampingTime = L.GetGlobalFloat("stampingTime", status);
		data->coyoteTime = L.GetGlobalFloat("coyoteTime", status);
		data->stopVelocityThreshold = L.GetGlobalFloat("stopVelocityThreshold", status);
		data->numberOfJumps = L.GetGlobalInt("numberOfJumps", status);

		return data;
	}

}

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

		m_data = GetInitialCrazyAgentConfigurationDataFromLuaFile();

		// creation
		m_ecsWorld = std::make_shared<JojoECS>(*m_data);
		m_ecsWorld->SetTilemapMovementSolver(collisionTilemapSolver);
		m_factory = std::make_shared<JojoFactory>(m_ecsWorld->engine(), playerIndex, *m_data);
		
		//m_playerEntity = m_factory->makePlayerFreeMover(100, 250);
		
		//m_playerEntity = m_factory->makePlayer(100, 250);
		m_playerEntity = m_factory->makeCrazyPlayer(100, 100);

		auto tilemapNode = aether::GEngine->CreateTilemapNode(m_tilemap);
		auto mapHeightInPixels = m_tilemap->GetTotalHeightInPixels();

		m_tilemap->GetObjectLayer("enemies")->ForEachObject([this, mapHeightInPixels](const auto& o) {
			const auto& type = o.props.at("type");
			auto x = o.aabb.center().GetX();
			auto y = o.aabb.center().GetY();
			if (type == "dumbwalker") {
				m_factory->makeBallEnemy(x, mapHeightInPixels - y - 1 - 3);
			}
		});

		auto viewport = aether::math::Vec2f {
				float(JojoConfig::instance().windowWidth),
				float(JojoConfig::instance().windowHeight) };
		auto cam = aether::GEngine->GetCamera(aether::render::CameraFlags::Default);
		cam->SetOrthographicSize(2.f);
		cam->SetPosition(100.f, 100.f, -500.f);

		m_platformerScroll = std::make_shared<aether::render::PlatformerScroller>(
					cam, aether::math::Rectf(0, 0, m_tilemap->GetTotalWidthInPixels(), m_tilemap->GetTotalHeightInPixels()),
					aether::math::Vec2f(800, 500));

		m_topDownScroll = std::make_shared<aether::render::TopDownMapScroller>();
		m_topDownScroll->Setup(cam, {{ 0, 0 }, { float(m_tilemap->GetTotalWidthInPixels()), float(m_tilemap->GetTotalHeightInPixels())}});
		m_directScroller = std::make_shared<aether::render::DirectScroller>(cam);
		
		aether::GEngine->ToggleImGuiStats();

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
		/*
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
		*/
		//auto aabb = m_ecsWorld->engine().GetComponent<AABBComponent>(m_playerEntity).aabb;
		//aether::GEngine->GetInstantRenderer()->DrawAABB({ {aabb.x1(), aabb.y1(), 0}, {aabb.x2(), aabb.y2(), 100.f}}, aether::render::Color::Green, -1);
	}


	void JojoWorld::Update(double delta)
	{
		m_ecsWorld->step(delta);
		// DoDirectScrolling();
		DoTopDownScrolling();
		// DoPlatformerScrolling(delta);
	}

	void JojoWorld::DoPlatformerScrolling(float deltaInSeconds)
	{
		auto& pc = m_ecsWorld->engine().GetComponent<TransformComponent>(m_playerEntity);
		auto& tc = m_ecsWorld->engine().GetComponent<TilemapCollisionComponent>(m_playerEntity);
		auto& aabbc = m_ecsWorld->engine().GetComponent<AABBComponent>(m_playerEntity);
		auto& rendercomp = m_ecsWorld->engine().GetComponent<RenderComponent>(m_playerEntity);

		auto pos = rendercomp.sprite->GetWorldPosition();
		auto aabb = aabbc.aabb;

		m_platformerScroll->Update(deltaInSeconds);

		m_platformerScroll->SetSnapToPlatform(tc.lastCollisionInfo.yCollisionNormal == 1);

		if( tc.lastCollisionInfo.yCollisionNormal == 1 )
		{
			m_platformerScroll->SnapToPlatform(pc.position.GetY());
		}
	}

	void JojoWorld::DoTopDownScrolling()
	{
		auto& pc = m_ecsWorld->engine().GetComponent<TransformComponent>(m_playerEntity);
		auto& tc = m_ecsWorld->engine().GetComponent<TilemapCollisionComponent>(m_playerEntity);
		auto& aabbc = m_ecsWorld->engine().GetComponent<AABBComponent>(m_playerEntity);
		auto& rendercomp = m_ecsWorld->engine().GetComponent<RenderComponent>(m_playerEntity);

		auto pos = rendercomp.sprite->GetWorldPosition();
		auto aabb = aabbc.aabb;

		m_topDownScroll->Focus(pos.x + aabb.w() / 2.f, pos.y + aabb.h() / 2.f);
		//m_topDownScroll->Focus(pc.position.GetX(), pc.position.GetY());
	}
	
	void JojoWorld::DoDirectScrolling()
	{
		auto& pc = m_ecsWorld->engine().GetComponent<TransformComponent>(m_playerEntity);
		auto& tc = m_ecsWorld->engine().GetComponent<TilemapCollisionComponent>(m_playerEntity);
		auto& aabbc = m_ecsWorld->engine().GetComponent<AABBComponent>(m_playerEntity);
		auto& rendercomp = m_ecsWorld->engine().GetComponent<RenderComponent>(m_playerEntity);

		auto pos = rendercomp.sprite->GetWorldPosition();
		auto aabb = aabbc.aabb;
		m_directScroller->Focus(pos.x + aabb.w() / 2.f, pos.y + aabb.h() / 2.f);
		//m_directScroller->Focus(pos.x, pos.y);
		//m_directScroller->Focus(aabb.x() + aabb.w() / 2.f, aabb.y() + aabb.h() / 2.f);
		//m_directScroller->Focus(aabb.x(), aabb.y());
	}

	const secs::Engine& JojoWorld::GetECSWorld() const
	{
		return m_ecsWorld->engine();
	}

}
