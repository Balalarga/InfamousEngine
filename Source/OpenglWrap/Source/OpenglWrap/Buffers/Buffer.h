#pragma once

#include <GL/glew.h>

#include "BufferLayout.h"
#include "DataPtr.h"

namespace Inf
{
struct Buffer
{
    Buffer() = default;
    Buffer(const DataPtr& data, BufferLayout layout);

    DataPtr Data;
    BufferLayout Layout;

    Buffer& SetDrawType(int type);
    Buffer& SetType(int type);
    Buffer& SetMode(int type);

    int DrawType = GL_TRIANGLES;
    int Type = GL_ARRAY_BUFFER;
    int Mode = GL_STATIC_DRAW;

    unsigned Create();
};
}
