#include <Dunjun/Mesh.hpp>

namespace Dunjun
{
Mesh::Mesh()
: m_data()
, m_generated(false)
, m_vbo(0)
, m_ibo(0)
, m_drawType(GL_TRIANGLES)
, m_drawCount(0)
{
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);
}

Mesh::Mesh(const Data& data)
: m_data(data)
, m_generated(false)
, m_vbo(0)
, m_ibo(0)
, m_drawType(GL_TRIANGLES)
, m_drawCount(0)
{
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);

	generate();
}

void Mesh::generate()
{
	if (m_generated)
		return;

	m_drawType = m_data.drawType;
	m_drawCount = m_data.indices.size();

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER,
	             sizeof(Vertex) * m_data.vertices.size(),
	             &m_data.vertices[0],
	             GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
	             sizeof(u32) * m_data.indices.size(),
	             &m_data.indices[0],
	             GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	m_generated = true;
}

void Mesh::draw()
{
	if (!m_generated)
		generate();
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glEnableVertexAttribArray((u32)AtrribLocation::Position);
	glEnableVertexAttribArray((u32)AtrribLocation::Color);
	glEnableVertexAttribArray((u32)AtrribLocation::TexCoord);

	glVertexAttribPointer(0,
	                      3,
	                      GL_FLOAT,
	                      GL_FALSE,
	                      sizeof(Vertex), // Stride
	                      (const GLvoid*)(0));
	glVertexAttribPointer(1,
	                      4,
	                      GL_UNSIGNED_BYTE, // 0-255 => 0-1
	                      GL_TRUE,
	                      sizeof(Vertex), // Stride
	                      (const GLvoid*)(sizeof(Vector3)));
	glVertexAttribPointer(2,
	                      2,
	                      GL_FLOAT,
	                      GL_FALSE,
	                      sizeof(Vertex), // Stride
	                      (const GLvoid*)(sizeof(Vector3) + sizeof(Color)));

	glDrawElements(m_drawType, m_drawCount, GL_UNSIGNED_INT, nullptr);

	glDisableVertexAttribArray((u32)AtrribLocation::Position);
	glDisableVertexAttribArray((u32)AtrribLocation::Color);
	glDisableVertexAttribArray((u32)AtrribLocation::TexCoord);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

} // namespace Dunjun
