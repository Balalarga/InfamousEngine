#include "Engine.h"
#include <spdlog/spdlog.h>
#include <LLGL/LLGL.h>


Engine::Engine()
{
}

void Engine::Start()
{
	LLGL::WindowDescriptor windowDesc;
	windowDesc.title = L"LLGL Example";
	windowDesc.size.width = 1280;
	windowDesc.size.height = 720;

	auto window = LLGL::Window::Create(windowDesc);
	auto input = std::make_shared<LLGL::Input>();
	struct EventListener: public LLGL::Window::EventListener
	{
		void OnKeyDown(LLGL::Window& sender, LLGL::Key keyCode) override
		{
			spdlog::info("KeyDown");
		}
	};
	auto SharedListener = std::make_shared<EventListener>();
	window->AddEventListener(SharedListener);
	input->Listen(*window);

	window->Show(true);
	while (window->ProcessEvents() && window->IsShown())
	{
	}
}