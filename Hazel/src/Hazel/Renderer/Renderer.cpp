#include "hzpch.h"
#include "Renderer.h"

#include "RendererCommand.h"

namespace Hazel
{
	Renderer::SceneData* Renderer::m_SceneData = new SceneData();

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->UpdateUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);

		vertexArray->Bind();
		RendererCommand::DrawIndexed(vertexArray);
	}
}