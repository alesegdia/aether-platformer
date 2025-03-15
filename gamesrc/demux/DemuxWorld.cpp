#include "DemuxWorld.h"
#include "DemuxEcs.h"
#include "DemuxFactory.h"
#include "DemuxConfig.h"


namespace Demux {

	int DemuxWorld::Init()
	{
		m_ecsWorld = std::make_shared<DemuxECS>();
		return 0;
	}

	void DemuxWorld::Render()
	{
		if(m_ecsWorld != nullptr)
		{
			m_ecsWorld->render();
		}
		else
		{
			aether::Logger::LogError() << "DemuxWorld::Render: m_ecsWorld is nullptr";
		}
	}

	void DemuxWorld::Update(double delta)
	{
		if (m_ecsWorld != nullptr)
		{
			m_ecsWorld->step(delta);
		}
		else
		{
			aether::Logger::LogError() << "DemuxWorld::Update: m_ecsWorld is nullptr";
		}
	}

	const secs::Engine& DemuxWorld::GetECSWorld() const
	{
		return m_ecsWorld->engine();
	}

}
