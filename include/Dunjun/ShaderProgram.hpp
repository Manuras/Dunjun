#ifndef DUNJUN_SHADERPROGRAM_HPP
#define DUNJUN_SHADERPROGRAM_HPP

#include <Dunjun/Common.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

namespace Dunjun
{
enum class ShaderType
{
	Vertex,
	Fragment,
};

class ShaderProgram
{
public:
	ShaderProgram();
	virtual ~ShaderProgram();

	bool attachShaderFromFile(ShaderType type, const std::string& filename);
	bool attachShaderFromMemory(ShaderType type, const std::string& filename);

	void use() const;
	bool isInUse() const;
	void stopUsing() const;

	bool link();
	bool isLinked();

	void bindAttribLocation(GLuint location, const GLchar* name);

	GLint getAttribLocation(const GLchar* name);
	GLint getUniformLocation(const GLchar* name);

	void setUniform(const GLchar* name, float x);
	void setUniform(const GLchar* name, float x, float y);
	void setUniform(const GLchar* name, float x, float y, float z);
	void setUniform(const GLchar* name, float x, float y, float z, float w);
	void setUniform(const GLchar* name, unsigned int x);
	void setUniform(const GLchar* name, int x);
	void setUniform(const GLchar* name, bool x);

	inline GLuint object() const { return m_object; }
	inline const std::string& errorLog() const { return m_errorLog; }

private:
	GLuint m_object;
	bool m_linked;
	std::string m_errorLog;
};
} // namespace Dunjun

#endif