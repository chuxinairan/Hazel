#include "hazel.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Hazel::VertexArray::Create());

		float vertices[] = {
			 0.5, -0.5, 0.0,   1.0, 0.0, 1.0, 1.0,
			-0.5, -0.5, 0.0,   0.0, 1.0, 1.0, 1.0,
			 0.0,  0.5, 0.0,   1.0, 1.0, 0.0, 1.0
		};

		Hazel::Ref<Hazel::VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(Hazel::VertexBuffer::Create(vertices, sizeof(vertices)));
		Hazel::BufferLayout layout = {
			{ Hazel::ShaderDataType::Float3, "a_Position"},
			{ Hazel::ShaderDataType::Float4, "a_Color"},
		};
		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		unsigned int indices[] = { 0, 1, 2 };

		Hazel::Ref<Hazel::IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);


		m_SquareVA.reset(Hazel::VertexArray::Create());

		float squareVertices[] = {
			 0.5, -0.5, 0.0, 1.0, 0.0,
			 0.5,  0.5, 0.0, 1.0, 1.0,
			-0.5,  0.5, 0.0, 0.0, 1.0,
			-0.5, -0.5, 0.0, 0.0, 0.0
		};

		Hazel::Ref<Hazel::VertexBuffer> m_SquareVB;
		m_SquareVB.reset(Hazel::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		Hazel::BufferLayout squareLayout = {
			{ Hazel::ShaderDataType::Float3, "a_Position"},
			{ Hazel::ShaderDataType::Float2, "a_TexCoord"},
		};
		m_SquareVB->SetLayout(squareLayout);
		m_SquareVA->AddVertexBuffer(m_SquareVB);

		unsigned int squareIndices[] = { 0, 1, 2, 2, 3, 0 };

		Hazel::Ref<Hazel::IndexBuffer> m_SquareIB;
		m_SquareIB.reset(Hazel::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(m_SquareIB);

		std::string vertexSrc = R"(
			#version 330 core
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			out vec3 v_Position;
			out vec4 v_Color;
			uniform mat4 u_ViewProjection;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";
		std::string fragmentSrc = R"(
			#version 330 core
			layout(location = 0) out vec4 o_Color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				o_Color = vec4(v_Position * 0.5 + 0.5, 1.0) + v_Color * 0.5;
			}
		)";
		m_Shader.reset(Hazel::Shader::Create(vertexSrc, fragmentSrc));

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			layout(location = 0) in vec3 a_Position;
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";
		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			layout(location = 0) out vec4 o_Color;
			uniform vec4 u_Color;
			void main()
			{
				o_Color = u_Color;
			}
		)";
		m_FlatColorShader.reset(Hazel::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));

		m_TextureShader.reset(Hazel::Shader::Create("assets/shaders/Texture.glsl"));

		m_Texture = Hazel::Texture2D::Create("assets/textures/Checkerboard.png");
		m_ChernoTexture = Hazel::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Hazel::Timestep timestep) override
	{
		HZ_TRACE("Timestep: {0}s ({1}ms)", timestep.GetSeconds(), timestep.GetMilliseconds());
		if (Hazel::Input::IsKeyPressed(HZ_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * timestep;
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * timestep;

		if (Hazel::Input::IsKeyPressed(HZ_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * timestep;
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * timestep;

		if (Hazel::Input::IsKeyPressed(HZ_KEY_A))
			m_CameraRotation -= m_CameraRotateSpeed * timestep;
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_D))
			m_CameraRotation += m_CameraRotateSpeed * timestep;

		Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Hazel::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Hazel::Renderer::BeginScene(m_Camera);

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);
		glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);

		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);
		for (int j = 0; j < 20; j++)
		{
			for (int i = 0; i < 20; i++)
			{
				glm::vec3 pos = glm::vec3(i * 0.11f, j * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

				Hazel::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		m_Texture->Bind();
		Hazel::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_ChernoTexture->Bind();
		Hazel::Renderer::Submit(m_TextureShader, m_SquareVA, glm::translate(glm::mat4(1.0f), glm::vec3(0.25f, 0.25f, 0)) * glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		//Hazel::Renderer::Submit(m_Shader, m_VertexArray);

		Hazel::Renderer::EndScene();

	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Hazel::Event& e) override
	{
	}
	
private:
	Hazel::Ref<Hazel::Shader> m_Shader;
	Hazel::Ref<Hazel::VertexArray> m_VertexArray;

	Hazel::Ref<Hazel::Shader> m_FlatColorShader, m_TextureShader;
	Hazel::Ref<Hazel::VertexArray> m_SquareVA;

	Hazel::Ref<Hazel::Texture2D> m_Texture, m_ChernoTexture;

	Hazel::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 05.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotateSpeed = 180.0f;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};

class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox(){}
};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
};