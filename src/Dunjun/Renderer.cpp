#include <Dunjun/Renderer.hpp>

#include <string>

namespace Dunjun
{

	Renderer::Renderer()
	{
	}

	void Renderer::reset()
	{
		if (m_currentShaders)
			m_currentShaders->stopUsing();
		m_currentShaders = nullptr;

		m_currentTexture = nullptr;
		Texture::bind(nullptr, 0);

		m_currentCamera = nullptr;
	}

	void Renderer::setShaders(ShaderProgram* shaders)
	{
		if (shaders != m_currentShaders && m_currentShaders)
			m_currentShaders->stopUsing();
		m_currentShaders = shaders;
		m_currentShaders->use();
	}

	void Renderer::setTexture(const Texture* texture)
	{
		if (texture != m_currentTexture)
		{
			m_currentTexture = texture;

			Texture::bind(m_currentTexture, 0);
		}
	}

	void Renderer::setCamera(const Camera& camera)
	{
		m_currentCamera = &camera;
	}

	void Renderer::setUniforms(const Transform& t)
	{
		if (!m_currentShaders)
			return;
		else if (!m_currentShaders->isInUse())
			m_currentShaders->use();

		m_currentShaders->setUniform("u_camera", m_currentCamera->getMatrix());

		m_currentShaders->setUniform("u_transform", t);
		m_currentShaders->setUniform("u_tex", (u32)0);
	}

} // namespace Dunjun