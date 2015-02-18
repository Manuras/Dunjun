#ifndef DUNJUN_SHADERPROGRAM_HPP
#define DUNJUN_SHADERPROGRAM_HPP

#include <Dunjun/OpenGL.hpp>
#include <Dunjun/NonCopyable.hpp>

#include <Dunjun/Common.hpp>

#include <Dunjun/Math.hpp>
#include <Dunjun/Transform.hpp>

#include <map>
#include <string>

namespace Dunjun
{
enum class ShaderType
{
	Vertex,
	Fragment,
};

class ShaderProgram : public NonCopyable
{
public:
	ShaderProgram();
	virtual ~ShaderProgram();

	bool attachShaderFromFile(ShaderType type, const std::string& filename);
	bool attachShaderFromMemory(ShaderType type, const std::string& filename);

	void use() const;
	bool isInUse() const;
	void stopUsing() const;
	void checkInUse() const; // if not in use, will throw a std::runtime_error

	bool link();
	bool isLinked();

	void bindAttribLocation(GLuint location, const std::string& name);

	GLint getAttribLocation(const std::string& name);
	GLint getUniformLocation(const std::string& name);

	void setUniform(const std::string& name, f32 x);
	void setUniform(const std::string& name, f32 x, f32 y);
	void setUniform(const std::string& name, f32 x, f32 y, f32 z);
	void setUniform(const std::string& name, f32 x, f32 y, f32 z, f32 w);
	void setUniform(const std::string& name, u32 x);
	void setUniform(const std::string& name, s32 x);
	void setUniform(const std::string& name, bool x);
	void setUniform(const std::string& name, const Vector2& v);
	void setUniform(const std::string& name, const Vector3& v);
	void setUniform(const std::string& name, const Vector4& v);
	void setUniform(const std::string& name, const Matrix4& m);
	void setUniform(const std::string& name, const Quaternion& t);
	void setUniform(const std::string& name, const Transform& t);

	inline GLuint getObject() const { return m_object; }
	inline const std::string& getErrorLog() const { return m_errorLog; }

private:
	GLuint m_object;
	bool m_linked;
	std::string m_errorLog;

	std::map<std::string, GLint> m_attribLocations;
	std::map<std::string, GLint> m_uniformLocations;
};
} // namespace Dunjun

#endif
