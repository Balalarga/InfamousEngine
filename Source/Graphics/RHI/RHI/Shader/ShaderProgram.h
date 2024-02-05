#pragma once
#include <memory>
#include <vector>


#include "Shader.h"
#include "RenderTarget/IRenderBindable.h"
#include "Resource/VRamResource.h"


namespace Inf
{
class ShaderProgram: public VRamResource, public IRenderBindable
{
public:
	ShaderProgram();
	
	bool AttachShader(const std::shared_ptr<Shader>& newShader);
	
	void Bind() override;
	
	
protected:
	void PostAllocate() override;
	std::optional<THandle> Allocate() override;
	void Deallocate(const THandle& handler) override;

	void ReleaseImpl() override;


private:
	std::vector<std::shared_ptr<Shader>> _shaders;
};
}
