#include "##GAMENAME##World.h"
#include "##GAMENAME##Ecs.h"
#include "##GAMENAME##Factory.h"
#include "##GAMENAME##Config.h"


namespace ##GAMENAME## {

	int ##GAMENAME##World::Init()
	{
		m_ecsWorld = std::make_shared<##GAMENAME##ECS>();
		return 0;
	}

	void ##GAMENAME##World::Render()
	{
		if(m_ecsWorld != nullptr)
		{
			m_ecsWorld->render();
		}
		else
		{
			aether::Logger::LogError() << "##GAMENAME##World::Render: m_ecsWorld is nullptr";
		}
	}

	void ##GAMENAME##World::Update(double delta)
	{
		if (m_ecsWorld != nullptr)
		{
			m_ecsWorld->step(delta);
		}
		else
		{
			aether::Logger::LogError() << "##GAMENAME##World::Update: m_ecsWorld is nullptr";
		}
	}

	const secs::Engine& ##GAMENAME##World::GetECSWorld() const
	{
		return m_ecsWorld->engine();
	}

}
