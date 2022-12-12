#pragma once

namespace ogw
{
class SystemManager;

class Application
{
public:
	Application();
	virtual ~Application();

	void Run();
	
	virtual void Init() = 0;
	virtual void Destroy() = 0;

	SystemManager& GetSystemManager() const { return _systemManager; }
	
private:
	SystemManager& _systemManager;
};
}