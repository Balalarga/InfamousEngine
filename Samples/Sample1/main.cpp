#include <iostream>

#include "ISerializable.h"
#include "GlfwWindow/GlfwWindow.h"
#include "Stream/FileStream.h"

using namespace Inf;

class A: public ISerializable
{
public:
	void Serialize(IStream& stream) override
	{
		stream << a;
		stream << string;
	}
	int a;
	std::string string;
};

int main(int, char**)
{
	A a;
	// a.a = 10;
	// a.string = "Hellow";
	std::string filepath = "test.txt";
	FileStream stream(filepath, Stream::Mode::Load);
	if (!stream)
		return -1;

	stream << a;
	std::cout << a.a << std::endl;
	std::cout << a.string << std::endl;
	
	Window::WindowParams params;
	params.fps = 60;
	
	const std::unique_ptr<Window::IWindow> window = std::make_unique<Window::GlfwWindow>(params);
	
	window->Run();
	
	return 0;
}
