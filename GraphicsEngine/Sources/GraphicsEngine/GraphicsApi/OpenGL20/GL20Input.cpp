#include "GL20Input.h"
#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20.h"
#include "GraphicsEngine/Internal/InternalInput.h"

#ifdef CAN_USE_OPEN_GL


void GL20Input::Init()
{
	// TODO : Task08
}

void GL20Input::Clear()
{
	InternalInput::Clear();
}

void GL20Input::SetLetterKeyDown(unsigned char key)
{
	// TODO : Task08
	// Call InternalInput
}

void GL20Input::SetLetterKeyUp(unsigned char key)
{
	// TODO : Task08
	// Call InternalInput
}

void GL20Input::SetSpecialKeyDown(unsigned char key)
{
	// TODO : Task08
	// Call InternalInput
}

void GL20Input::SetSpecialKeyUp(unsigned char key)
{
	// TODO : Task08
	// Call InternalInput
}

void GL20Input::SetMouseButtonsEvent(int button, int state, int x, int y)
{
	// TODO : Task08
	// Call InternalInput
}

void GL20Input::SetMouseMotionEvent(int x, int y)
{
	// TODO : Task08
	// Call InternalInput
}

#endif
