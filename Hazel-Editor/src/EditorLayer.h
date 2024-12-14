#pragma once

#include "hazel.h"

namespace Hazel
{
	class EditorLayer : public Hazel::Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(Hazel::Timestep timestep) override;
		virtual void OnEvent(Hazel::Event& event) override;
		virtual void OnImGuiRender() override;
	private:
		OrthographicCameraController m_CameraController;

		// Temp
		Ref<Hazel::VertexArray> m_SquareVA;
		Ref<Hazel::Shader> m_FlatColorShader;

		Ref<Hazel::Texture2D> m_CheckerboardTexture;

		Ref<Hazel::Framebuffer> m_Framebuffer;

		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	};
}