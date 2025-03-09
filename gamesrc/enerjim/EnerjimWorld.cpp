#include "EnerjimWorld.h"
#include "EnerjimEcs.h"
#include "EnerjimFactory.h"
#include "EnerjimConfig.h"

#include "aether/lua/lua.h"

#include "aether/plugin/platformer/ecs/component/TransformComponent.h"
#include "aether/plugin/platformer/ecs/component/AABBComponent.h"
#include "aether/plugin/platformer/ecs/component/RenderComponent.h"
#include "aether/plugin/platformer/ecs/component/VaniaJumper/VaniaJumperAgentComponent.h"
#include "aether/plugin/platformer/ecs/component/GravityComponent.h"

#include "aether/plugin/platformer/ecs/component/TilemapCollisionComponent.h"

#include "aether/map/AetherTilemapCollisionQueryInterface.h"

namespace enerjim {

	int EnerjimWorld::Init()
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
		auto playerIndex = m_tilemap->GetObjectLayer("entities")->GetDepthOrder();
		auto collisionLayer = m_tilemap->GetTileLayer("collision");
		auto collisionTilemap = std::make_shared<aether::tilemap::AetherTilemapCollisionQueryInterface>(collisionLayer);
		auto collisionTilemapSolver = std::make_shared<aether::tilemap::TilemapMovementSolver>(collisionTilemap);
		collisionTilemap->SetInvertedY(true);
		collisionTilemapSolver->SetOneWayUp(true);

		// creation
		m_ecsWorld = std::make_shared<EnerjimECS>();
		m_ecsWorld->SetTilemapMovementSolver(collisionTilemapSolver);
		m_factory = std::make_shared<EnerjimFactory>(m_ecsWorld->engine(), playerIndex);
		
		//m_playerEntity = m_factory->makePlayerFreeMover(100, 250);
		
		//m_playerEntity = m_factory->makePlayer(100, 250);

		auto spawn = m_tilemap->GetObjectLayer("entities")->GetObjectByName("playerSpawn");
		auto layerOrder = m_tilemap->GetLayerOrder("entities");
		auto objectTilePosition = m_tilemap->GetObjectTilePosition(*spawn);
		// auto objectLayerIndex = object.tileLayerIndex;
		auto spawnTile = glm::ivec2{ objectTilePosition.x, m_tilemap->GetHeightInTiles() - objectTilePosition.y };
		m_playerEntity = m_factory->MakePlayer(spawnTile.x * 32, spawnTile.y * 32); // , objectLayerIndex * 10);
		// m_playerEntity = m_factory->MakePlayer(100, 100);

		auto tilemapNode = aether::GEngine->CreateTilemapNode(m_tilemap, 10.f);
		auto mapHeightInPixels = m_tilemap->GetTotalHeightInPixels();

		auto viewport = aether::math::Vec2f {
				float(EnerjimConfig::instance().GetWindowWidth()),
				float(EnerjimConfig::instance().GetWindowHeight()) };
		auto cam = aether::GEngine->GetCamera(aether::render::CameraFlags::Default);
		cam->SetOrthographicSize(EnerjimConfig::instance().GetOrthoScale());
		cam->SetPosition(100.f, 100.f, -100.f);

		m_platformerScroll = std::make_shared<aether::render::PlatformerScroller>(
					cam, aether::math::Rectf(0, 0, m_tilemap->GetTotalWidthInPixels(), m_tilemap->GetTotalHeightInPixels()),
					aether::math::Vec2f(800, 500));

		m_topDownScroll = std::make_shared<aether::render::TopDownMapScroller>();
		m_topDownScroll->Setup(cam, {{ 0, 0 }, { float(m_tilemap->GetTotalWidthInPixels()), float(m_tilemap->GetTotalHeightInPixels())}});
		m_directScroller = std::make_shared<aether::render::DirectScroller>(cam);
		
		aether::GEngine->ToggleImGuiStats();

		aether::GEngine->GetCamera(aether::render::CameraFlags::Default)->SetZPosition(-500);

		return 0;
	}

	int EnerjimWorld::LoadMapFromLua(Tmx::Map& map)
	{
		if (EnerjimConfig::instance().GetStartingMapPath() == "")
		{
			return -1;
		}
		else
		{
			map.ParseFile(EnerjimConfig::instance().GetStartingMapPath());
			return 0;
		}
	}

	void EnerjimWorld::Render()
	{
		auto& pos = m_ecsWorld->engine().GetComponent<TransformComponent>(m_playerEntity).position;

		// m_platformerScroll->Focus(pos.GetX(), pos.GetY());
		m_ecsWorld->render();

		//DebugTilemap();

	}

	void EnerjimWorld::DebugTilemap()
	{
		auto zOffset = 400;
		auto collisionLayer = m_tilemap->GetTileLayer("collision");
		for (int i = 0; i < m_tilemap->GetWidthInTiles(); i++)
		{
			for (int j = 0; j < m_tilemap->GetHeightInTiles(); j++)
			{
				auto collisionBehaviour = collisionLayer->GetTileCollisionBehaviour(i, m_tilemap->GetHeightInTiles() - j - 1);
				if(collisionBehaviour.GetType() == aether::tilemap::TileCollisionBehaviourType::Oneway)
				{
					float tw = m_tilemap->GetTileWidth();
					float th = m_tilemap->GetTileHeight();
					// draw AABB for tile
					aether::GEngine->GetInstantRenderer()->DrawAABB({ {i * tw, j * th, zOffset}, {(i+1) * tw, (j+1) * th, zOffset + 10} }, aether::render::Color::Red);

					//aether::GEngine->GetInstantRenderer()->DrawAABB({ {}, {} }, aether::render::Color::Blue);
				}
			}
		}
		auto aabb = m_ecsWorld->engine().GetComponent<AABBComponent>(m_playerEntity).aabb;
		aether::GEngine->GetInstantRenderer()->DrawAABB({ {aabb.x1(), aabb.y1(), 0}, {aabb.x2(), aabb.y2(), 100.f}}, aether::render::Color::Green, -1);
	}


	void EnerjimWorld::Update(double delta)
	{
		if (m_ecsWorld != nullptr)
		{
			m_ecsWorld->step(delta);
			// DoDirectScrolling();
			DoTopDownScrolling();
			// DoPlatformerScrolling(delta);
		}
		else
		{
			aether::Logger::LogError() << "EnerjimWorld::Update: m_ecsWorld is nullptr";
		}
		DebugTilemap();
	}

	void EnerjimWorld::DoPlatformerScrolling(float deltaInSeconds)
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

	void EnerjimWorld::DoTopDownScrolling()
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
	
	void EnerjimWorld::DoDirectScrolling()
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

	const secs::Engine& EnerjimWorld::GetECSWorld() const
	{
		return m_ecsWorld->engine();
	}

}
