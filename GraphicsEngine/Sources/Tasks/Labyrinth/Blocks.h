#pragma once
enum Block
{
	FLOOR,
	WALL,
	LAVA, 
	LIGHTWALL,
	VISITED,		//служебное, используется для генерации лабиринта
	FINISHPOINT,
	FINISHWALL,
	STARTPOINT
};