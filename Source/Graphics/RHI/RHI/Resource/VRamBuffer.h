#pragma once
#include <type_traits>
#include <vector>
#include <gl/glew.h>

#include "VRamResource.h"


namespace Inf
{
class VRamBufferLayout
{
	struct VarInfo
	{
		GLuint Type;
		GLint Count;
		unsigned Size;
		GLboolean Normalized = GL_FALSE;
	};


public:
	VRamBufferLayout& Float(GLuint count);
	VRamBufferLayout& Int(GLuint count);
	VRamBufferLayout& Unsigned(GLuint count);

	const std::vector<VarInfo>& Variables() const;
	GLsizei Size() const;
	

private:
	std::vector<VarInfo> _varInfos;
	unsigned _size = 0;
};

template <typename T>
concept HasVramLayout = requires(T v)
{
	{ T::GetVramLayout() } -> std::convertible_to<VRamBufferLayout>;
};


class VRamBuffer: protected VRamResource
{
public:
	enum class Type: unsigned
	{
		Array = GL_ARRAY_BUFFER,
		ElementArray = GL_ELEMENT_ARRAY_BUFFER,
		CopyRead = GL_COPY_READ_BUFFER,
		CopyWrite = GL_COPY_WRITE_BUFFER,
		Texture = GL_TEXTURE_BUFFER,
		Uniform = GL_UNIFORM_BUFFER,
		Query = GL_QUERY_BUFFER
	};

	enum class UsageMode: unsigned
	{
		StaticDraw = GL_STATIC_DRAW,
		StaticRead = GL_STATIC_READ,
		StaticCopy = GL_STATIC_COPY,
		StreamDraw = GL_STREAM_DRAW,
		StreamRead = GL_STREAM_READ,
		StreamCopy = GL_STREAM_COPY,
		DynamicDraw = GL_DYNAMIC_DRAW,
		DynamicRead = GL_DYNAMIC_READ,
		DynamicCopy = GL_DYNAMIC_COPY
	};

	
	VRamBuffer(VRamBufferLayout layout);

	template<HasVramLayout T>
	VRamBuffer(std::vector<T>& data);

	
	VRamBuffer& BindData(void* ptr, unsigned size, unsigned count);
	
	template<class T>
	VRamBuffer& BindData(std::vector<T>& data);

	
	VRamBuffer& SetType(Type type);
	VRamBuffer& SetUsageMode(UsageMode usageMode);

	
	Type GetType() const;
	UsageMode GetUsageMode() const;

	
	using VRamResource::IsValid;
	using VRamResource::Build;
	

protected:
	THandler Allocate() override;


private:
	const VRamBufferLayout _layout;
	
	std::underlying_type_t<Type> _type;
	std::underlying_type_t<UsageMode> _usageMode;
	
	struct
	{
		void* Ptr = nullptr;
		unsigned Size = 0;
		unsigned Count = 0;
	} _data {};
};


template<HasVramLayout T>
VRamBuffer::VRamBuffer(std::vector<T>& data): VRamBuffer(T::GetVramLayout())
{
	BindData(data);
}

template<class T>
VRamBuffer& VRamBuffer::BindData(std::vector<T>& data)
{
	BindData(static_cast<void*>(data.data()), sizeof(T), data.size());
	return *this;
}
}
