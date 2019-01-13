#pragma once
#include <ctime>
#include <vector>
#include <stack>
#include "Tasks/Labyrinth/Blocks.h"


typedef unsigned short ushort;
typedef std::pair<ushort, ushort> Cell;
typedef std::vector<std::pair<ushort, ushort>> Neighbours;
typedef std::stack<Cell> CellStack;

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
				if (i > 0 && i < x - 1 && j > 0 && j < y - 1)  //только границы! - для тестирования
					field[i][j] = FLOOR;
				else
					field[i][j] = WALL;

				
				/*if (i % 2 != 0 && j % 2 != 0)  //+ границы если четные xy? - для алгоритма
				{
					field[i][j] = FLOOR;
					unvisited++;
				}
				else
					field[i][j] = WALL;*/
			}
		}

		field[5][5] = WALL;
		field[5][7] = WALL;

		Cell curCell;
		
		curCell = {1, 1};

		srand(time(0));

		/*do
		{
			Neighbours neighbours = getNeighbours(curCell);
			int size;
			if ((size = neighbours.size()) != 0)
			{
				int random = rand() % size;
			}

		} while (unvisited > 0);*/


		//первый проход: по какому-то алгоритму с хабра
		//потом ещё добавить лаву (можно её даже анимировать) - вместо стен (вместо пола чревато)

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

private:
	Neighbours getNeighbours(Cell curCell)
	{
		ushort cx = curCell.first;
		ushort cy = curCell.second;

		Cell u = { cx, cy - 2 };
		Cell d = { cx, cy - 2 };
		Cell r = { cx + 2, cy };
		Cell l = { cx - 2, cy };

		Neighbours neighbours = { u, d, r, l }, retNeighbours;

		for (Cell cell : neighbours)
		{
			if (cell.first >= 0 && cell.first < x && cell.second >= 0 && cell.second < y)
			{
				Block block = field[cell.first][cell.second];
				if (block != WALL && block != VISITED)
					retNeighbours.push_back(cell);
			}
		}
		return retNeighbours;
	}

	void removeWall(Cell c1, Cell c2)
	{

	}
};