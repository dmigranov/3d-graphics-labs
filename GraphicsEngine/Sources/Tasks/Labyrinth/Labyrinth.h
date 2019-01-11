

class Labyrinth
{
private:
	unsigned char ** field;
	unsigned short x, y;

public:
	Labyrinth(unsigned short x, unsigned short y)
	{
		this.x = x;
		this.y = y;

		field = new unsigned char*[x];
		for(unsigned short i = 0; i < x; i++)
		{
			field[i] = new unsigned char[y];
		}
		field[0];
		//первый проход: по какому-то алгоритму с хабра
		//потом ещё добавить лаву (можно её даже анимировать)

	}

};