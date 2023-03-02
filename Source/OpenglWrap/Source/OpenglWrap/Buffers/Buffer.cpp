#include "Buffer.h"
#include <GL/glew.h>

namespace Inf
{
Buffer::Buffer(const DataPtr& data, BufferLayout layout):
    Data(data),
    Layout(std::move(layout))
{

}

Buffer& Buffer::SetDrawType(int type)
{
    DrawType = type;
    return *this;
}

Buffer& Buffer::SetType(int type)
{
    Type = type;
    return *this;
}

Buffer& Buffer::SetMode(int type)
{
    Mode = type;
    return *this;
}

void Buffer::Create()
{
    if (!Data.Ptr)
        return;
    
    glGenBuffers(1, &_handler);
    glBindBuffer(Type, _handler);
    glBufferData(Type, Data.Count * Data.ItemSize, Data.Ptr, Mode);

    int64_t offset = 0;
    for (unsigned i = 0; i < Layout.Variables.size(); ++i)
    {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i,
                              Layout.Variables[i].Count,
                              Layout.Variables[i].Type,
                              Layout.Variables[i].Normalized ? GL_FALSE : GL_TRUE,
                              Layout.Size,
                              (void*)offset);
        offset += Layout.Variables[i].Size * Layout.Variables[i].Count;
    }
}
}