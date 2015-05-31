#include <Dunjun/ShaderProgram.hpp>

#include <Dunjun/Common.hpp>

#include <fstream>
#include <iostream>

namespace Dunjun
{
std::vector<std::string> split(const std::string& s, char delim)
{
	std::vector<std::string> elems;

	const char* cstr{s.c_str()};
	usize strLength{s.length()};
	usize start{0};
	usize end{0};

	while (end <= strLength)
	{
		while (end <= strLength)
		{
			if (cstr[end] == delim)
				break;
			end++;
		}

		elems.emplace_back(s.substr(start, end - start));
		start = end + 1;
		end = start;
	}

	return elems;
}

// TODO(bill): Customize to be specific for shader files
// #include <> & #include ""
INTERNAL std::string stringFromFile(const std::string& filename)
{
	std::ifstream file;
	file.open(std::string{BaseDirectory::Shaders + filename.c_str()},
	          std::ios::in | std::ios::binary);

	std::string fileDirectory{getFileDirectory(filename) + "/"};

	std::string output;
	std::string line;

	if (!file.is_open())
	{
		throwRuntimeError(std::string("Failed to open file : ") + filename);
	}
	else
	{
		while (file.good())
		{
			std::getline(file, line);

			if (line.find("#include") == std::string::npos)
			{
				output.append(line + "\n");
			}
			else
			{
				std::string includeFilename{split(line, ' ')[1]};

				if (includeFilename[0] == '<') // Absolute Path (library path)
				{
					usize closingBracketPos{0};
					for (usize i{1}; i < includeFilename.length(); i++)
					{
						if (includeFilename[i] == '>')
						{
							closingBracketPos = i;
							break;
						}
					}

					if (closingBracketPos > 1)
					{
						includeFilename =
						    includeFilename.substr(1, closingBracketPos - 1);
					}
					else
					{
						includeFilename = "";
					}
				}
				else if (includeFilename[0] == '\"') // Relative Path (folder path)
				{
					usize closingSpeechMark{0};
					for (usize i{1}; i < includeFilename.length(); i++)
					{
						if (includeFilename[i] == '\"')
						{
							closingSpeechMark = i;
							break;
						}
					}

					if (closingSpeechMark > 1)
						includeFilename = includeFilename.substr(1, closingSpeechMark - 1);
					else
						includeFilename = "";
				}

				// std::cout << includeFilename << '\n';

				if (includeFilename.length() > 0)
					output.append(stringFromFile(includeFilename) + "\n");
			}
		}
	}

	file.close();
	return output;
}

ShaderProgram::ShaderProgram()
: m_handle{0}
, m_isLinked{false}
, m_errorLog{}
{
}

ShaderProgram::~ShaderProgram()
{
	if (m_handle)
		glDeleteProgram(m_handle);
}

bool ShaderProgram::attachShaderFromFile(ShaderType type,
                                         const std::string& filename)
{
	std::string source{stringFromFile(filename)};
	return attachShaderFromMemory(type, source);
}

bool ShaderProgram::attachShaderFromMemory(ShaderType type,
                                           const std::string& source)
{
	if (!m_handle)
		m_handle = glCreateProgram();

	const char* shaderSource{source.c_str()};

	u32 shader;
	if (type == ShaderType::Vertex)
		shader = glCreateShader(GL_VERTEX_SHADER);
	else if (type == ShaderType::Fragment)
		shader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(shader, 1, &shaderSource, nullptr);
	glCompileShader(shader);

	s32 status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == false)
	{
		std::string msg;
		if (type == ShaderType::Vertex)
			msg = "Compile failure in vertex shader: \n";
		else if (type == ShaderType::Fragment)
			msg = "Compile failure in fragment shader: \n";

		s32 infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* strInfoLog{new char[infoLogLength + 1]};
		glGetShaderInfoLog(shader, infoLogLength, nullptr, strInfoLog);
		msg.append(strInfoLog);
		delete[] strInfoLog;

		msg.append("\n");

		m_errorLog.append(msg);

		glDeleteShader(shader);

		return false;
	}

	glAttachShader(m_handle, shader);

	return true;
}

void ShaderProgram::use() const
{
	if (!isInUse())
		glUseProgram(m_handle);
}

bool ShaderProgram::isInUse() const
{
	s32 currentProgram{0};
	glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);

	return (currentProgram == (s32)m_handle);
}

void ShaderProgram::stopUsing() const
{
	if (isInUse())
		glUseProgram(0);
}

void ShaderProgram::checkInUse() const
{
	if (!isInUse())
		throwRuntimeError("ShaderProgram not is use.");
}

bool ShaderProgram::link()
{
	if (!m_handle)
		m_handle = glCreateProgram();

	if (!m_isLinked)
	{
		glLinkProgram(m_handle);

		s32 status;
		glGetProgramiv(m_handle, GL_LINK_STATUS, &status);
		if (!status)
		{
			std::string msg{"ShaderProgram linking failure: \n"};

			s32 infoLogLength;
			glGetProgramiv(m_handle, GL_INFO_LOG_LENGTH, &infoLogLength);
			char* strInfoLog{new char[infoLogLength + 1]};
			glGetProgramInfoLog(m_handle, infoLogLength, nullptr, strInfoLog);
			msg.append(strInfoLog);
			delete[] strInfoLog;

			msg.append("\n");
			m_errorLog.append(msg);

			glDeleteProgram(m_handle);
			m_handle = 0;

			m_isLinked = false;
			return m_isLinked;
		}

		m_isLinked = true;
	}

	return m_isLinked;
}

u32 ShaderProgram::getNativeHandle() const { return m_handle; }

bool ShaderProgram::isLinked() const { return m_isLinked; }

const std::string& ShaderProgram::getErrorLog() const { return m_errorLog; }

void ShaderProgram::bindAttribLocation(u32 location, const std::string& name)
{
	glBindAttribLocation(m_handle, location, name.c_str());
	m_attribLocations[name] = location;
}

s32 ShaderProgram::getAttribLocation(const std::string& name) const
{
	auto found = m_attribLocations.find(name);
	if (found != std::end(m_attribLocations))
		return found->second;

	s32 loc{glGetAttribLocation(m_handle, name.c_str())};
	m_attribLocations[name] = loc;
	return loc;
}

s32 ShaderProgram::getUniformLocation(const std::string& name) const
{
	auto found = m_uniformLocations.find(name);
	if (found != std::end(m_uniformLocations))
		return found->second;

	s32 loc{glGetUniformLocation(m_handle, name.c_str())};
	m_uniformLocations[name] = loc;
	return loc;
}

void ShaderProgram::setUniform(const std::string& name, f32 x) const
{
	checkInUse();
	s32 loc{getUniformLocation(name)};
	if (loc == -1)
		return;
	glUniform1f(loc, x);
}

void ShaderProgram::setUniform(const std::string& name, f32 x, f32 y) const
{
	checkInUse();
	s32 loc{getUniformLocation(name)};
	if (loc == -1)
		return;
	glUniform2f(loc, x, y);
}

void ShaderProgram::setUniform(const std::string& name,
                               f32 x,
                               f32 y,
                               f32 z) const
{
	checkInUse();
	s32 loc{getUniformLocation(name)};
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
	s32 loc{getUniformLocation(name)};
	if (loc == -1)
		return;
	glUniform4f(loc, x, y, z, w);
}

void ShaderProgram::setUniform(const std::string& name, u32 x) const
{
	checkInUse();
	s32 loc{getUniformLocation(name)};
	if (loc == -1)
		return;
	glUniform1ui(loc, x);
}

void ShaderProgram::setUniform(const std::string& name, s32 x) const
{
	checkInUse();
	s32 loc{getUniformLocation(name)};
	if (loc == -1)
		return;
	glUniform1i(loc, x);
}

void ShaderProgram::setUniform(const std::string& name, bool x) const
{
	checkInUse();
	s32 loc{getUniformLocation(name)};
	if (loc == -1)
		return;
	glUniform1i(loc, (s32)x);
}

void ShaderProgram::setUniform(const std::string& name, const Vector2& v) const
{
	checkInUse();
	s32 loc{getUniformLocation(name)};
	if (loc == -1)
		return;
	glUniform2fv(loc, 1, &v[0]);
}

void ShaderProgram::setUniform(const std::string& name, const Vector3& v) const
{
	checkInUse();
	s32 loc{getUniformLocation(name)};
	if (loc == -1)
		return;
	glUniform3fv(loc, 1, &v[0]);
}

void ShaderProgram::setUniform(const std::string& name, const Vector4& v) const
{
	checkInUse();
	s32 loc{getUniformLocation(name)};
	if (loc == -1)
		return;
	glUniform4fv(loc, 1, &v[0]);
}

void ShaderProgram::setUniform(const std::string& name, const Matrix4& m) const
{
	checkInUse();
	s32 loc{getUniformLocation(name)};
	if (loc == -1)
		return;
	glUniformMatrix4fv(loc, 1, false, &m[0][0]);
}

void ShaderProgram::setUniform(const std::string& name,
                               const Quaternion& t) const
{
	checkInUse();
	s32 loc{getUniformLocation(name)};
	if (loc == -1)
		return;
	glUniform4fv(loc, 1, &t.data[0]);
}

void ShaderProgram::setUniform(const std::string& name,
                               const Transform& t) const
{
	checkInUse();
	{
		s32 loc{getUniformLocation(name + ".position")};
		if (loc == -1)
			return;
		glUniform3fv(loc, 1, &t.position[0]);
	}
	{
		s32 loc{getUniformLocation(name + ".orientation")};
		if (loc == -1)
			return;
		glUniform4fv(loc, 1, &t.orientation[0]);
	}
	{
		s32 loc{getUniformLocation(name + ".scale")};
		if (loc == -1)
			return;
		glUniform3fv(loc, 1, &t.scale[0]);
	}
}

void ShaderProgram::setUniform(const std::string& name, const Color& c) const
{
	f32 r{c.r / 255.0f};
	f32 g{c.g / 255.0f};
	f32 b{c.b / 255.0f};
	f32 a{c.a / 255.0f};

	setUniform(name, r, g, b, a);
}
} // namespace Dunjun
