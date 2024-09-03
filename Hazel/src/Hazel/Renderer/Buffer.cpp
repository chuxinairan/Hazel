#include "hzpch.h"
#include "Buffer.h"

#include "Hazel/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Hazel
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::NONE: HZ_CORE_ASSERT(false, "NONE currently is not supported!"); return nullptr; break;
		case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}
		HZ_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::NONE: HZ_CORE_ASSERT(false, "NONE currently is not supported!"); return nullptr; break;
		case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, size);
		}
		HZ_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}