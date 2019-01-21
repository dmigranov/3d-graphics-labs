#pragma once

class GUIImpl
{
public:
	virtual void Label(int x, int y, int w, int h, const char * pText) = 0;
	virtual void Rectangle(int x, int y, int w, int h, int r, int g, int b) = 0;
};
