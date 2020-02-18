#include <SFML/Graphics.hpp>

using namespace  sf; 

//Вспомогательный класс для рисования рамки для кнопок и элементов интерфейса
class Border
{
public:
	static RectangleShape printBorder(float xSize, float ySize, float x, float y)
	{
		RectangleShape border(Vector2f(xSize, ySize));
		border.setFillColor(Color(15, 14, 14));
		border.setOutlineColor(Color(198, 36, 36));
		border.setOutlineThickness(2);
		border.setPosition(x, y);
		return border;
	}
	static bool restart;
};
