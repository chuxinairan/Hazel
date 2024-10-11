#pragma once
#include "Hazel/Core/core.h"
#include "Hazel/Core/Timestep.h"
#include "Hazel/Events/Event.h"

namespace Hazel
{
	class HAZEL_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach(){}
		virtual void OnDetach(){}
		virtual void OnUpdate(Timestep timestep){}
		virtual void OnEvent(Event& event){}
		virtual void OnImGuiRender(){}

		inline const std::string& GetName() const { return m_DebugName; }
	private:
		const std::string m_DebugName;
	};
}


