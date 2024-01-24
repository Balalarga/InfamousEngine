#pragma once


namespace Inf
{

class IRenderBindable
{
public:
	virtual ~IRenderBindable() = default;

	virtual void Bind() = 0;

	virtual void Release();

	bool NeedRelease() const;
	void SetNeedRelease(bool state);


protected:
	virtual void ReleaseImpl() = 0;


private:
	bool _needRelease = false;
};

}