#include "hzpch.h"
#include "OrthographicCameraController.h"

#include "Hazel/Core/Input.h"
#include "Hazel/Core/KeyCodes.h"
#include "Hazel/Core/core.h"

namespace Hazel
{
	OrthographicCameraController::OrthographicCameraController(float aspectRadio, bool rotation)
		: m_AspectRadio(aspectRadio), m_Camera(-m_AspectRadio * m_ZoomLevel, m_AspectRadio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{
	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		HZ_PROFILE_FUNCTION();

		if (Input::IsKeyPressed(HZ_KEY_A))
			m_CameraPosition.x -= m_CameraTranslateSpeed * ts;
		else if (Input::IsKeyPressed(HZ_KEY_D))
			m_CameraPosition.x += m_CameraTranslateSpeed * ts;

		if (Input::IsKeyPressed(HZ_KEY_S))
			m_CameraPosition.y -= m_CameraTranslateSpeed * ts;
		else if (Input::IsKeyPressed(HZ_KEY_W))
			m_CameraPosition.y += m_CameraTranslateSpeed * ts;
		
		if (m_Rotation) {
			if (Input::IsKeyPressed(HZ_KEY_Q))
				m_CameraRotation -= m_CameraRotateSpeed * ts;
			else if (Input::IsKeyPressed(HZ_KEY_E))
				m_CameraRotation += m_CameraRotateSpeed * ts;
			m_Camera.SetRotation(m_CameraRotation);
		}
		m_Camera.SetPosition(m_CameraPosition);
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		HZ_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>(HZ_EVENT_CALLBACK_FN(OrthographicCameraController::OnWindowResized));
		dispatcher.Dispatch<MouseScrolledEvent>(HZ_EVENT_CALLBACK_FN(OrthographicCameraController::OnMouseScrolled));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		HZ_PROFILE_FUNCTION();

		m_ZoomLevel -= e.GetYOffset() * 0.5f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRadio * m_ZoomLevel, m_AspectRadio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return true;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		HZ_PROFILE_FUNCTION();

		m_AspectRadio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRadio * m_ZoomLevel, m_AspectRadio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return true;
	}
}
