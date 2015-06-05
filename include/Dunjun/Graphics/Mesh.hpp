#ifndef DUNJUN_GRAPHICS_MESH_HPP
#define DUNJUN_GRAPHICS_MESH_HPP

#include <Dunjun/System/OpenGL.hpp>
#include <Dunjun/Common.hpp>
#include <Dunjun/Graphics/Vertex.hpp>

#include <vector>

namespace Dunjun
{
class SceneRenderer;
enum class AtrribLocation : u32
{
	Position = 0,
	TexCoord = 1,
	Color    = 2,
	Normal   = 3,
};

enum class DrawType : s32
{
	Points        = GL_POINTS,
	Lines         = GL_LINES,
	LineStrip     = GL_LINE_STRIP,
	LineLoop      = GL_LINE_LOOP,
	Triangles     = GL_TRIANGLES,
	TriangleStrip = GL_TRIANGLE_STRIP,
	TriangleFan   = GL_TRIANGLE_FAN,
	// Quads      = GL_QUADS, // Disabled by default
};

class Mesh
{
public:
	struct Data
	{
		DrawType drawType{DrawType::Triangles};

		VertexArray vertices;
		std::vector<u32> indices;

		Data& addFace(u32 a, u32 b, u32 c)
		{
			indices.emplace_back(a);
			indices.emplace_back(b);
			indices.emplace_back(c);

			return *this;
		}

		Data& addFace(u32 offset, u32 a, u32 b, u32 c)
		{
			indices.emplace_back(offset + a);
			indices.emplace_back(offset + b);
			indices.emplace_back(offset + c);

			return *this;
		}

		void generateNormals();
	};

	Mesh();
	Mesh(const Data& data);

	virtual ~Mesh() { destroy(); }

	void addData(const Data& data);

	void generate() const;

private:
	// NOTE(bill): Only Renderers can draw a mesh
	friend class SceneRenderer;

	inline void destroy() const
	{
		if (m_vbo)
			glDeleteBuffers(1, &m_vbo);
		if (m_ibo)
			glDeleteBuffers(1, &m_ibo);
	}


	void draw() const;

	Data m_data;

	// NOTE(bill): These mutables are a little bit of a hack but it works and
	// is semi-const correct

	mutable u32 m_vbo{0};
	mutable u32 m_ibo{0};

	mutable bool m_generated{false};

	DrawType m_drawType{DrawType::Triangles};
	s32 m_drawCount{0};
};
} // namespace Dunjun

#endif
