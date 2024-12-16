#pragma once
#include "Hazel/Renderer/Framebuffer.h"

namespace Hazel {
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		virtual ~OpenGLFramebuffer();
		void Invalidate();
		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; }
		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; }
	private:
		uint32_t m_RendererID = 0; // FBO标识符
		uint32_t m_ColorAttachment = 0, m_DepthAttachment = 0; // 颜色纹理和深度纹理
		FramebufferSpecification m_Specification;
	};
}