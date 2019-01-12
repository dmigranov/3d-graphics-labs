#pragma once
#include "Tasks/Labyrinth/Blocks.h"

typedef unsigned short ushort;

class Labyrinth
{
private:
	Block ** field;
	ushort x, y;

public:
	Labyrinth(ushort x, ushort y)
	{
		this->x = x;
		this->y = y;

		field = new Block*[x];
		for(ushort i = 0; i < x; i++)
		{
			field[i] = new Block[y];
		}
		
		for (ushort i = 0; i < x; i++)
		{
			for (ushort j = 0; j < y; j++)
			{
				/*if (i % 2 != 0 && j % 2 != 0)  //�������?/
					field[i][j] = FLOOR;
				else
					field[i][j] = WALL;*/
				if (i > 0 && i < x - 1 && j > 0 && j < y - 1)  //�������?/
					field[i][j] = FLOOR;
				else
					field[i][j] = WALL; 

			}
		}


		

		//������ ������: �� ������-�� ��������� � �����
		//����� ��� �������� ���� (����� � ���� �����������) - ������ ����

	}

	ushort getX()
	{
		return x;
	}

	ushort getY()
	{
		return y;
	}

	Block getAt(ushort x, ushort y)
	{
		return field[x][y];
	}

	Block ** getField()
	{
		return field;
	}

};