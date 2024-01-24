#include "VRamBuffer.h"


namespace Inf
{
VRamBufferLayout& VRamBufferLayout::Float(GLuint count)
{
	_varInfos.push_back({GL_FLOAT, static_cast<int>(count), sizeof(GLfloat)}); _size += count * sizeof(GLfloat);
	return *this;
}

VRamBufferLayout& VRamBufferLayout::Int(GLuint count)
{
	_varInfos.push_back({GL_INT, static_cast<int>(count), sizeof(GLint)}); _size += count * sizeof(GLint);
	return *this;
}

VRamBufferLayout& VRamBufferLayout::Unsigned(GLuint count)
{
	_varInfos.push_back({GL_UNSIGNED_INT, static_cast<int>(count), sizeof(GLuint)}); _size += count * sizeof(GLuint);
	return *this;
}

const std::vector<VRamBufferLayout::VarInfo>& VRamBufferLayout::Variables() const
{
	return _varInfos;
}

GLsizei VRamBufferLayout::Size() const
{
	return static_cast<GLsizei>(_size);
}

VRamBuffer::VRamBuffer(VRamBufferLayout layout)
	: _layout(std::move(layout))
	, _type(static_cast<std::underlying_type_t<Type>>(Type::Array))
	, _usageMode(static_cast<std::underlying_type_t<UsageMode>>(UsageMode::StaticDraw))
{
}

VRamBuffer& VRamBuffer::BindData(void* ptr, unsigned size, unsigned count)
{
	_data.Count = count;
	_data.Size = size;
	_data.Ptr = ptr;
	return *this;
}

VRamBuffer& VRamBuffer::SetType(Type type)
{
	_type = static_cast<std::underlying_type_t<Type>>(type);
	return *this;
}

VRamBuffer& VRamBuffer::SetUsageMode(UsageMode usageMode)
{
	_usageMode = static_cast<std::underlying_type_t<UsageMode>>(usageMode);
	return *this;
}

VRamBuffer::Type VRamBuffer::GetType() const
{
	return static_cast<Type>(_type);
}

VRamBuffer::UsageMode VRamBuffer::GetUsageMode() const
{
	return static_cast<UsageMode>(_usageMode);
}

std::optional<VRamResource::THandler> VRamBuffer::Allocate()
{
	unsigned handler = 0;
	// TODO: exception here
	if (!_data.Ptr || _data.Count == 0 || _data.Size == 0)
		return {};
	
	glGenBuffers(1, &handler);
	glBindBuffer(_type, handler);
	glBufferData(_type, _data.Count * _data.Size, _data.Ptr, _usageMode);

	unsigned offset = 0;
	for (unsigned i = 0; i < _layout.Variables().size(); ++i)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i,
							  _layout.Variables()[i].Count,
							  _layout.Variables()[i].Type,
							  _layout.Variables()[i].Normalized,
							  _layout.Size(),
							  (void*)offset);
		offset += _layout.Variables()[i].Size * _layout.Variables()[i].Count;
	}

	return static_cast<THandler>(handler);
}
}
