#pragma once
#include "GL20.h"
#include "GraphicsEngine/GraphicsApi/GUIImpl.h"


class GL20GUI : public GUIImpl
{
public:
	void Label(int x, int y, int w, int h, const char * pText);
	void Rectangle(int x, int y, int w, int h, int r, int g, int b);
};
