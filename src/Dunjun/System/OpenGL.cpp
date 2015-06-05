#include <Dunjun/System/OpenGL.hpp>
#include <Dunjun/System/Types.hpp>

#include <type_traits>

namespace Dunjun
{
// Verify types
static_assert(std::is_same<GLubyte, u8>::value,
              "GLubyte is not the same as u8.");
static_assert(std::is_same<GLbyte, s8>::value,
              "GLbyte is not the same as s8.");
static_assert(std::is_same<GLushort, u16>::value,
              "GLushort is not the same as u16.");
static_assert(std::is_same<GLshort, s16>::value,
              "GLshort is not the same as s16.");
static_assert(std::is_same<GLuint, u32>::value,
              "GLuint is not the same as u32.");
static_assert(std::is_same<GLint, s32>::value,
              "GLint is not the same as s32.");
static_assert(std::is_same<GLsizei, s32>::value,
              "GLsizei is not the same as s32.");
static_assert(std::is_same<GLfloat, f32>::value,
              "GLfloat is not the same as f32.");

// Verify boolean values
static_assert(GL_FALSE == false,
              "GL_FALSE is not the same as false.");
static_assert(GL_TRUE == true,
              "GL_TRUE is not the same as true.");
} // namespace Dunjun
