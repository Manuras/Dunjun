#include <Dunjun/ShaderProgram.hpp>

#include <fstream>

namespace Dunjun
{
// TODO(bill): Customize to be specific for shader files
//             #include <> & #include ""
//             // comments
INTERNAL std::string stringFromFile(const std::string& filename)
{
	std::ifstream file;
	file.open(filename.c_str(), std::ios::in | std::ios::binary);

	std::string output;
	std::string line;

	if (!file.is_open())
	{
		std::runtime_error(std::string("Failed to open file: ") + filename);
	}
	else
	{
		while (file.good())
		{
			getline(file, line);

			output.append(line + "\n");
		}
	}

	file.close();
	return output;
}

ShaderProgram::ShaderProgram()
: object(0)
, isLinked(false)
, errorLog()
{
	object = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
	if (object)
		glDeleteProgram(object);
}

bool ShaderProgram::attachShaderFromFile(ShaderType type,
                                         const std::string& filename)
{
	std::string source = stringFromFile(filename);
	return attachShaderFromMemory(type, source);
}

bool ShaderProgram::attachShaderFromMemory(ShaderType type,
                                           const std::string& source)
{
	if (!object)
		object = glCreateProgram();

	const char* shaderSource = source.c_str();

	GLuint shader;
	if (type == ShaderType::Vertex)
		shader = glCreateShader(GL_VERTEX_SHADER);
	else if (type == ShaderType::Fragment)
		shader = glCreateShader(GL_FRAGMENT_SHADER);
	else
		throw std::runtime_error("Shader type unknown. How did you get here?");

	glShaderSource(shader, 1, &shaderSource, nullptr);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		std::string msg("Compile failure in shader: \n");

		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* strInfoLog = new char[infoLogLength + 1];
		glGetShaderInfoLog(shader, infoLogLength, nullptr, strInfoLog);
		msg.append(strInfoLog);
		delete[] strInfoLog;

		msg.append("\n");

		errorLog.data.append(msg);

		glDeleteShader(shader);

		return false;
	}

	glAttachShader(object, shader);

	return true;
}

void ShaderProgram::use() const
{
	if (!isInUse())
		glUseProgram(object);
}

bool ShaderProgram::isInUse() const
{
	GLint currentProgram = 0;
	glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);

	return (currentProgram == (GLint)object);
}

void ShaderProgram::stopUsing() const
{
	if (isInUse())
		glUseProgram(0);
}

void ShaderProgram::checkInUse() const
{
	if (!isInUse())
		throw std::runtime_error("ShaderProgram not is use.");
}

bool ShaderProgram::link()
{
	if (!object)
		object = glCreateProgram();

	if (!isLinked)
	{
		glLinkProgram(object);

		GLint status;
		glGetProgramiv(object, GL_LINK_STATUS, &status);
		if (status == GL_FALSE)
		{
			std::string msg("ShaderProgram linking failure: \n");

			GLint infoLogLength;
			glGetProgramiv(object, GL_INFO_LOG_LENGTH, &infoLogLength);
			char* strInfoLog = new char[infoLogLength + 1];
			glGetProgramInfoLog(object, infoLogLength, nullptr, strInfoLog);
			msg.append(strInfoLog);
			delete[] strInfoLog;

			msg.append("\n");
			errorLog.data.append(msg);

			glDeleteProgram(object);
			object = 0;

			isLinked = false;
			return isLinked;
		}

		isLinked = true;
	}

	return isLinked;
}

void ShaderProgram::bindAttribLocation(GLuint location, const std::string& name)
{
	glBindAttribLocation(object, location, name.c_str());
	m_attribLocations[name] = location;
}

GLint ShaderProgram::getAttribLocation(const std::string& name) const
{
	auto found = m_attribLocations.find(name);
	if (found != m_attribLocations.end())
		return found->second;

	GLint loc = glGetAttribLocation(object, name.c_str());
	m_attribLocations[name] = loc;
	return loc;
}

GLint ShaderProgram::getUniformLocation(const std::string& name) const
{
	auto found = m_uniformLocations.find(name);
	if (found != m_uniformLocations.end())
		return found->second;

	GLint loc = glGetUniformLocation(object, name.c_str());
	m_uniformLocations[name] = loc;
	return loc;
}

void ShaderProgram::setUniform(const std::string& name, f32 x) const
{
	checkInUse();
	GLint loc = getUniformLocation(name);
	if (loc == -1)
		return;
	glUniform1f(loc, x);
}

void ShaderProgram::setUniform(const std::string& name, f32 x, f32 y) const
{
	checkInUse();
	GLint loc = getUniformLocation(name);
	if (loc == -1)
		return;
	glUniform2f(loc, x, y);
}

void ShaderProgram::setUniform(const std::string& name, f32 x, f32 y, f32 z) const
{
	checkInUse();
	GLint loc = getUniformLocation(name);
	if (loc == -1)
		return;
	glUniform3f(loc, x, y, z);
}

void ShaderProgram::setUniform(const std::string& name,
                               f32 x,
                               f32 y,
                               f32 z,
							   f32 w) const
{
	checkInUse();
	GLint loc = getUniformLocation(name);
	if (loc == -1)
		return;
	glUniform4f(loc, x, y, z, w);
}

void ShaderProgram::setUniform(const std::string& name, u32 x) const
{
	checkInUse();
	GLint loc = getUniformLocation(name);
	if (loc == -1)
		return;
	glUniform1ui(loc, x);
}

void ShaderProgram::setUniform(const std::string& name, s32 x) const
{
	checkInUse();
	GLint loc = getUniformLocation(name);
	if (loc == -1)
		return;
	glUniform1i(loc, x);
}

void ShaderProgram::setUniform(const std::string& name, bool x) const
{
	checkInUse();
	GLint loc = getUniformLocation(name);
	if (loc == -1)
		return;
	glUniform1i(loc, (int)x);
}

void ShaderProgram::setUniform(const std::string& name, const Vector2& v) const
{
	checkInUse();
	GLint loc = getUniformLocation(name);
	if (loc == -1)
		return;
	glUniform2fv(loc, 1, &v[0]);
}

void ShaderProgram::setUniform(const std::string& name, const Vector3& v) const
{
	checkInUse();
	GLint loc = getUniformLocation(name);
	if (loc == -1)
		return;
	glUniform3fv(loc, 1, &v[0]);
}

void ShaderProgram::setUniform(const std::string& name, const Vector4& v) const
{
	checkInUse();
	GLint loc = getUniformLocation(name);
	if (loc == -1)
		return;
	glUniform4fv(loc, 1, &v[0]);
}

void ShaderProgram::setUniform(const std::string& name, const Matrix4& m) const
{
	checkInUse();
	GLint loc = getUniformLocation(name);
	if (loc == -1)
		return;
	glUniformMatrix4fv(loc, 1, GL_FALSE, &m[0][0]);
}

void ShaderProgram::setUniform(const std::string& name, const Quaternion& t) const
{
	checkInUse();
	GLint loc = getUniformLocation(name);
	if (loc == -1)
		return;
	glUniform4fv(loc, 1, &t.data[0]);
}

void ShaderProgram::setUniform(const std::string& name, const Transform& t) const
{
	checkInUse();

	setUniform(name + ".position", t.position);
	setUniform(name + ".orientation", t.orientation);
	setUniform(name + ".scale", t.scale);
}

void ShaderProgram::setUniform(const std::string& name, const Color& c) const
{
	f32 r, g, b, a;
	r = c.r / 255.0f;
	g = c.g / 255.0f;
	b = c.b / 255.0f;
	a = c.a / 255.0f;

	setUniform(name, r, g, b, a);
}
} // namespace Dunjun
