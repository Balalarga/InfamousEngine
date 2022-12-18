#include "BufferLayout.h"
#include <GL/glew.h>

namespace Inf
{
BufferLayout& BufferLayout::Float(int count)
{
	Variables.push_back({GL_FLOAT, count, sizeof(GLfloat)});
	Size += count * static_cast<int>(sizeof(GLfloat));
	return *this;
}

BufferLayout& BufferLayout::Int(int count)
{
	Variables.push_back({GL_INT, count, sizeof(GLint)});
	Size += count * static_cast<int>(sizeof(GLint));
	return *this;
}

BufferLayout& BufferLayout::Unsigned(int count)
{
	Variables.push_back({GL_UNSIGNED_INT, count, sizeof(GLuint)});
	Size += count * static_cast<int>(sizeof(GLuint));
	return *this;
}
}