#include "GameWindow.h"

#include <GL/glew.h>
#include <cassert>

#include "Opengl.h"

namespace Unk
{
static int sWindowCounter = 0;

GameWindow::GameWindow(const Initializer& initializer):
	_initializer(initializer),
	_inputManager(*this)
{
	if (sWindowCounter == 0)
		assert(SDL_Init(initializer.Subsystems) == 0);

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
		SDL_GL_DeleteContext(_openglContext);
		SDL_DestroyWindow(_sdlWindow);
		SDL_Quit();
	}
}

void GameWindow::Render()
{
	SDL_GL_SwapWindow(_sdlWindow);
}

uint32_t GameWindow::GetWindowId() const
{
	return SDL_GetWindowID(_sdlWindow);
}
}
