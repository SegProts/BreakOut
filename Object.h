class Object
{
public:

	//���������� ��� ��������� ���������� � ������� ���������
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

	//���������� ��� �������� �������� ����� (color �������� �� �������� ������������ ���������� �����)
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

	//��� ���� ����������� ��� ������������� ���� live, ������� ����� ��� ����������� ����� ������
	Object() { live = true; }

	int sizeX, sizeY;
	float x, y;
	float x1, x2, x3, x4, y1, y2, y3, y4;
	bool live;
	Color color;

	//����������� ����� � �������� (��� ������)
	bool catchButton(int x, int y)
	{

		if((x >= this->x1) && (x <= this->x2) && (y >= this->y1) && (y <= this->y3))
		{
			return true;
		}
		else { return false; }
	}

	//���������� ��������� 4-� ����� �������������� ��� ��� �����������
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

