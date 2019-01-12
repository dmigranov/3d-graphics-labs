#pragma once
#include <vector>
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
		
		unsigned int unvisited = 0;
		for (ushort i = 0; i < x; i++)
		{
			for (ushort j = 0; j < y; j++)
			{
				if (i > 0 && i < x - 1 && j > 0 && j < y - 1)  //������ �������!
					field[i][j] = FLOOR;
				else
					field[i][j] = WALL;

				
				/*if (i % 2 != 0 && j % 2 != 0)  //+ ������� ���� ������ xy? - ��� ���������
				{
					field[i][j] = FLOOR;
					unvisited++;
				}
				else
					field[i][j] = WALL;*/
			}
		}

		std::pair<ushort, ushort> curCell;
		curCell = {1, 1};

		/*do
		{
			std::vector<std::pair<ushort, ushort>> neighbours = getNeighbours();
			if (neighbours.size() != 0)
			{

			}

		} while (unvisited > 0);*/

		

		//������ ������: �� ������-�� ��������� � �����
		//����� ��� �������� ���� (����� � ���� �����������) - ������ ���� (������ ���� �������)

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