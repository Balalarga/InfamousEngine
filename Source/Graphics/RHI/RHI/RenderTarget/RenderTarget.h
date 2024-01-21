#pragma once


class IRenderTarget
{
public:
	IRenderTarget() = default;
	virtual ~IRenderTarget() = default;

	virtual void Clear() = 0;
	virtual void Bind() = 0;
	virtual void Release() = 0;
	virtual void Present() = 0;
};

