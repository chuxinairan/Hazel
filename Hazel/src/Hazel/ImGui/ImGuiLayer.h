#pragma once
#include "Hazel/Core/core.h"
#include "Hazel/Core/Layer.h"

#include "Hazel/Events/Event.h"
#include "Hazel/Events/Mouse.h"
#include "Hazel/Events/Keyboard.h"
#include "Hazel/Events/ApplicationEvent.h"

namespace Hazel
{
	class HAZEL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}
