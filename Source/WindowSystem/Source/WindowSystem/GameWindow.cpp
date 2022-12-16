#include "GameWindow.h"

#include <GL/glew.h>
#include <cassert>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl.h>

#include "Opengl.h"

namespace Inf
{
static int sWindowCounter = 0;

GameWindow::GameWindow(const Initializer& initializer):
	_initializer(initializer),
	_inputManager(*this)
{
	if (sWindowCounter == 0)
	{
		assert(SDL_Init(initializer.Subsystems) == 0);
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
	}

	_sdlWindow = SDL_CreateWindow(_initializer.Title.c_str(),
								  _initializer.Pos.x,
								  _initializer.Pos.y,
								  _initializer.Size.x,
								  _initializer.Size.y,
								  _initializer.Flags);
	assert(_sdlWindow);

	_openglContext = SDL_GL_CreateContext(_sdlWindow);
	assert(_openglContext);

	if (sWindowCounter == 0)
	{
		glewExperimental = GL_TRUE;
		assert(glewInit() == GLEW_OK);

		ImGui_ImplSDL2_InitForOpenGL(_sdlWindow, _openglContext);
		ImGui_ImplOpenGL3_Init(_initializer.imguiGlVersion);
	}

	SDL_GL_MakeCurrent(_sdlWindow, _openglContext);

	Opengl::SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	Opengl::SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	Opengl::SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	Opengl::SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	Opengl::SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	Opengl::SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	++sWindowCounter;
}

GameWindow::~GameWindow()
{
	--sWindowCounter;
	if (sWindowCounter == 0)
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();

		SDL_GL_DeleteContext(_openglContext);
		SDL_DestroyWindow(_sdlWindow);
		SDL_Quit();
	}
}

void GameWindow::Open()
{
	if (!_bIsClosed)
		return;

	_bIsClosed = false;
	SDL_ShowWindow(_sdlWindow);
}

void GameWindow::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Window");
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	SDL_GL_SwapWindow(_sdlWindow);
}

uint32_t GameWindow::GetWindowId() const
{
	return SDL_GetWindowID(_sdlWindow);
}
}
