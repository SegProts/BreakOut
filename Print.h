#include <SFML/Graphics.hpp>
#include <string>

using namespace  std;
using namespace  sf;

//��������������� �������������� ����� ��� ���������� ������
class Print
{
public:
	//����� ������ �� ���� � ����� ������
	static void setFont(string path) { font.loadFromFile(path); }

	//��������� ����� ��� ������
	static Text printText(string t, Color c = Color::White, int size = 14, Text::Style style = Text::Bold) //�����, ������ ������, �����
	{
		Text text(t, font, size);
		text.setFillColor(c);
		text.setStyle(style);
		return text;
	}

	//��������� ����� ��� ������
	static Text printText(wstring t, int size) //�����, ������ ������, �����
	{
		Text text(t, font, size);
		text.setFillColor(Color::Red);
		text.setStyle(Text::Bold);
		return text;
	}

	//��������� ����� ��� ������
	static Text printText(wstring t, int size, float x, float y) //�����, ������ �������
	{
		Text text(t, font, size);
		text.setPosition(x, y); //��������� ������� ������
		text.setFillColor(Color(198, 36, 36)); //����������� ������ ����� ������
		text.setStyle(Text::Bold);
		return text;
	}

	static Font font;
};
