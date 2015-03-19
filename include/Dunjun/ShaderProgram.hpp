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

	void bindAttribLocation(GLuint location, const std::string& name);

	GLint getAttribLocation(const std::string& name) const;
	GLint getUniformLocation(const std::string& name) const;

	void setUniform(const std::string& name, f32 x) const;
	void setUniform(const std::string& name, f32 x, f32 y) const;
	void setUniform(const std::string& name, f32 x, f32 y, f32 z) const;
	void setUniform(const std::string& name, f32 x, f32 y, f32 z, f32 w) const;
	void setUniform(const std::string& name, u32 x) const;
	void setUniform(const std::string& name, s32 x) const;
	void setUniform(const std::string& name, bool x) const;
	void setUniform(const std::string& name, const Vector2& v) const;
	void setUniform(const std::string& name, const Vector3& v) const;
	void setUniform(const std::string& name, const Vector4& v) const;
	void setUniform(const std::string& name, const Matrix4& m) const;
	void setUniform(const std::string& name, const Quaternion& t) const;
	void setUniform(const std::string& name, const Transform& t) const;

	ReadOnly<GLuint, ShaderProgram> object;
	ReadOnly<bool, ShaderProgram> isLinked;
	ReadOnly<std::string, ShaderProgram> errorLog;

private:
	mutable std::map<std::string, GLint> m_attribLocations;
	mutable std::map<std::string, GLint> m_uniformLocations;
};
} // namespace Dunjun

#endif
