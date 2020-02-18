#include <SFML/Graphics.hpp>
#include <string>

using namespace  std;
using namespace  sf;

//Вспомогательный статистический класс для распечатки текста
class Print
{
public:
	//Смена шрифта по пути к файлу шрифта
	static void setFont(string path) { font.loadFromFile(path); }

	//Формируем текст для печати
	static Text printText(string t, Color c = Color::White, int size = 14, Text::Style style = Text::Bold) //Текст, размер шрифта, стиль
	{
		Text text(t, font, size);
		text.setFillColor(c);
		text.setStyle(style);
		return text;
	}

	//Формируем текст для печати
	static Text printText(wstring t, int size) //Текст, размер шрифта, стиль
	{
		Text text(t, font, size);
		text.setFillColor(Color::Red);
		text.setStyle(Text::Bold);
		return text;
	}

	//Формируем текст для печати
	static Text printText(wstring t, int size, float x, float y) //Текст, размер позиция
	{
		Text text(t, font, size);
		text.setPosition(x, y); //Установка позиции текста
		text.setFillColor(Color(198, 36, 36)); //Определения своего цвета текста
		text.setStyle(Text::Bold);
		return text;
	}

	static Font font;
};
