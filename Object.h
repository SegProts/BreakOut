class Object
{
public:

	//Конструтор для элементов интерфейса и игровых элементов
	Object(int sizeX, int sizeY, float x, float y) 
	{
		this->sizeX = sizeX;
		this->sizeY = sizeY;
		this->x = x;
		this->y = y;

		this->x1 = x;
		this->y1 = y;

		this->x2 = x + sizeX;
		this->y2 = y1;

		this->x3 = x;
		this->y3 = y + sizeY;

		this->x4 = x + sizeX;
		this->y4 = y3;
		live = true;
	}

	//Конструтор для создание объектов ящика (color свойство по которому определяется начисление очков)
	Object(int sizeX, int sizeY, float x, float y, Color &color)
	{
		this->sizeX = sizeX;
		this->sizeY = sizeY;
		this->x = x;
		this->y = y;

		this->x1 = x;
		this->y1 = y;

		this->x2 = x + sizeX;
		this->y2 = y1;

		this->x3 = x;
		this->y3 = y + sizeY;

		this->x4 = x + sizeX;
		this->y4 = y3;
		live = true;
		this->color = color;
	}

	//Еще один конструктор для инициализации поля live, который нужен для определения целых ящиков
	Object() { live = true; }

	int sizeX, sizeY;
	float x, y;
	float x1, x2, x3, x4, y1, y2, y3, y4;
	bool live;
	Color color;

	//Пересечение точки с объектом (для кнопок)
	bool catchButton(int x, int y)
	{

		if((x >= this->x1) && (x <= this->x2) && (y >= this->y1) && (y <= this->y3))
		{
			return true;
		}
		else { return false; }
	}

	//Обновление координат 4-х точек прямоугольника при его перемещении
	void update(Vector2f position)
	{
		this->x1 = position.x;
		this->y1 = position.y;

		this->x2 = position.x + sizeX;
		this->y2 = y1;

		this->x3 = position.x;
		this->y3 = position.y + sizeY;

		this->x4 = x2;
		this->y4 = y3;
	}
};

