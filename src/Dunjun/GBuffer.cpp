#include <Dunjun/GBuffer.hpp>

#include <vector>

namespace Dunjun
{
GBuffer::GBuffer() {}

GBuffer::~GBuffer()
{
	if (m_fbo)
		glDeleteFramebuffersEXT(1, &m_fbo);
}

bool GBuffer::create(u32 w, u32 h)
{
	if (w == m_width && h == m_height)
		return true;

	m_width = w;
	m_height = h;

	if (!m_fbo)
		glGenFramebuffersEXT(1, &m_fbo);

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_fbo);

	GLuint depthRenderBuffer = 0;
	// The depth buffer
	glGenRenderbuffersEXT(1, &depthRenderBuffer);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depthRenderBuffer);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT,
	                         GL_DEPTH_COMPONENT,
							 (GLsizei)m_width,
	                         (GLsizei)m_height);
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT,
	                             GL_DEPTH_ATTACHMENT,
	                             GL_RENDERBUFFER_EXT,
	                             depthRenderBuffer);

	std::vector<GLenum> drawBuffers;

	auto addRT = [&drawBuffers, w, h](Texture& tex,
	                                  GLenum attactment,
	                                  GLint internalFormat,
	                                  GLenum format,
	                                  GLenum type)
	{
		if (!tex.m_object)
			glGenTextures(1, &tex.m_object);
		glBindTexture(GL_TEXTURE_2D, tex.m_object);
		glTexImage2D(GL_TEXTURE_2D,
		             0,
		             internalFormat,
		             (GLsizei)w,
		             (GLsizei)h,
		             0,
		             format,
		             type,
		             nullptr);
		tex.m_width = w;
		tex.m_height = h;

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glFramebufferTextureEXT(
		    GL_FRAMEBUFFER_EXT, attactment, tex.m_object, 0);

		if (attactment != GL_DEPTH_ATTACHMENT_EXT)
			drawBuffers.push_back(attactment);
	};

	addRT(diffuse, GL_COLOR_ATTACHMENT0_EXT, GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE);
	addRT(specular, GL_COLOR_ATTACHMENT1_EXT, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
	addRT(normal, GL_COLOR_ATTACHMENT2_EXT, GL_RGB10_A2, GL_RGBA, GL_FLOAT);
	addRT(depth, GL_DEPTH_ATTACHMENT_EXT, GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT, GL_FLOAT);

	glDrawBuffers(drawBuffers.size(), &drawBuffers[0]);

	if (glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT) !=
	    GL_FRAMEBUFFER_COMPLETE_EXT)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER_EXT, 0);
		return false;
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER_EXT, 0);
	return true;
}

void GBuffer::bind(const GBuffer* b)
{
	if (!b)
		glFlush();
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, b != nullptr ? b->m_fbo : 0);
}


u32 GBuffer::getWidth() const
{
	return m_width;
}
u32 GBuffer::getHeight() const
{
	return m_height;
}

GLuint GBuffer::getNativeHandle() const
{
	return m_fbo;
}
} // namespace Dunjun
