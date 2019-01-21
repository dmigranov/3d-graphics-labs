#include "GUI.h"
#include "GraphicsEngine/Internal/InternalGUI.h"


void GUI::Label(int x, int y, int w, int h, const std::string & text)
{
	InternalGUI::Label(x, y, w, h, text);
}

void GUI::Label(int x, int y, int w, int h, double number)
{
	InternalGUI::Label(x, y, w, h, number);
}

void GUI::Rectangle(int x, int y, int w, int h, int r, int g, int b)
{
	InternalGUI::Rectangle(x, y, w, h, r, g, b);
}
