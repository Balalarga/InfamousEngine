#include <iostream>

#include "ISerializable.h"
#include "GlfwWindow/GlfwWindow.h"
#include "Resource/VRamBuffer.h"
#include "Stream/FileStream.h"
#include "Stream/IStream.h"

using namespace Inf;

class A: public ISerializable
{
public:
	void Serialize(IStream& stream) override
	{
		stream << a << string;
	}
	
	int a;
	std::string string;
};


struct Vertex
{
	int x, y;
	float r, g, b, a;
	static VRamBufferLayout GetVramLayout()
	{
		return VRamBufferLayout().Int(2).Float(4);
	}
};

int main(int, char**)
{
	std::vector<Vertex> vertices;
	VRamBuffer buffer = VRamBuffer(vertices);
	if (!buffer.Build())
		return -1;
	
	std::string filepath = "test.txt";
	FileStream stream(filepath, Stream::Mode::Save, FileStream::Format::Text);
	if (!stream.Open())
		return -1;

	A a;
	a.a = 10;
	a.string = "Hellow";
	stream << a;
	std::cout << a.a << std::endl;
	std::cout << a.string << std::endl;
	
	Window::WindowParams params;
	params.fps = 60;
	
	const std::unique_ptr<Window::IWindow> window = std::make_unique<Window::GlfwWindow>(params);
	
	window->Run();
	
	return 0;
}
