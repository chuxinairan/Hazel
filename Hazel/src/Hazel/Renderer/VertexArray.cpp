#include "hzpch.h"
#include "VertexArray.h"

#include "Hazel/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Hazel
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::NONE: HZ_CORE_ASSERT(false, "NONE currently is not supported!"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLVertexArray();
		}
		HZ_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}