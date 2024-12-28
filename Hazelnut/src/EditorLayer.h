#pragma once

#include "hazel.h"

#include "Panels/SceneHierarchyPanel.h"
#include "Panels/ContentBrowserPanel.h"

#include "Hazel/Renderer/EditorCamera.h"

namespace Hazel
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(Hazel::Timestep timestep) override;
		virtual void OnEvent(Hazel::Event& event) override;
		virtual void OnImGuiRender() override;
		void OnScenePlay();
		void OnSceneStop();
		// UI Panels
		void UI_Toolbar();
	private:
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		void NewScene();
		void OpenScene();
		void OpenScene(const std::filesystem::path& path);
		void SaveSceneAs();
	private:
		// Temp
		Ref<Hazel::VertexArray> m_SquareVA;
		Ref<Hazel::Shader> m_FlatColorShader;
		Ref<Hazel::Framebuffer> m_Framebuffer;
		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

		Ref<Hazel::Texture2D> m_CheckerboardTexture;
		// Editor resources
		Ref<Texture2D> m_IconPlay, m_IconStop;

		Ref<Scene> m_ActiveScene;
		Entity m_SquareEntity;
		Entity m_CameraEntity;
		Entity m_SecondCamera;
		Entity m_HoveredEntity;
		bool m_PrimaryCamera = true;
		EditorCamera m_EditorCamera;
		OrthographicCameraController m_CameraController;

		enum class SceneState
		{
			Edit = 0, Play = 1
		};
		SceneState m_SceneState = SceneState::Edit;

		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		glm::vec2 m_ViewportBounds[2];

		// Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
		ContentBrowserPanel m_ContentBrowserPanel;

		int m_GizmoType = -1;
	};
}