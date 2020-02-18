#include <SFML/Graphics.hpp>
#include <string>
#include "Print.h"
#include "Border.h"
#include "Record.h"
#include "Game.h"

using namespace  sf;
using namespace  std;

Font Print::font; //���������� ��������������� ���� ��� ���������� �������������
				  
bool Border::restart = false; //���� ���� �� ������ ������ ������� � ���� ����

int main()
{
	RenderWindow menu, record, game;
	menu.create(VideoMode(600, 800), L"��������", Style::Titlebar);
	//window.create(VideoMode(600, 800), "Arcanoid");
	menu.setFramerateLimit(60); //����� ������� ������
	//menu.setMouseCursorVisible(false);
	menu.setActive(true);


	/*-------------������ � ��������-------------*/
	menu.setMouseCursorVisible(false); //�������� ��������� ������
	View fixed = menu.getView();

	//�������� ������ �������
	Texture moveTexture, selectTexture;
	moveTexture.loadFromFile("Data/Move.png"); //������ ��� ��������
	selectTexture.loadFromFile("Data/Select.png"); //������ ����� ���������� ����������� �������
	Sprite cursor(moveTexture);

	//��������� ������ �� ���������
	Print::setFont("Data/font.otf");
	//������� (x,y), ���������� (x,y), ���(true - ��������, false - ���������)
	RectangleShape border;

	int indexMenu = -1; //������ ��������� ������

	Object button1(155, 30, 225, 215), button2(210, 30, 200, 285), button3(160, 30, 225, 355);


	while (menu.isOpen())
	{
		
		//���� �� ������ ������ ������� � ���� Game
		if (Border::restart == true)
		{
			Border::restart = false;
			Game::Display(game, menu);
		}

		Event event;

		while (menu.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				menu.close();
				break;
			case Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//������ ������ ������
					if (button1.catchButton(Mouse::getPosition(menu).x, Mouse::getPosition(menu).y))
					{
						menu.setVisible(false);
						Game::Display(game, menu);
					}

					//������ ������ �������
					if (button2.catchButton(Mouse::getPosition(menu).x, Mouse::getPosition(menu).y))
					{
						menu.setVisible(false);
						Record::Render(record, menu);
					}

					//������ ������ �����
					if (button3.catchButton(Mouse::getPosition(menu).x, Mouse::getPosition(menu).y))
					{
						menu.close();
					}
				}
				break;
			case Event::KeyPressed:

				//������ Enter (��� ���������� ��������� � Enter)
				if (Keyboard::isKeyPressed(Keyboard::Return))
				{
					switch (indexMenu)
					{
					case 0:
						menu.setVisible(false);
						Game::Display(game, menu);
						break;
					case 1:
						menu.setVisible(false);
						Record::Render(record, menu);
						break;
					case 2:
						menu.close();
						break;

					}
				}

				break;
			}
		}

		/*----------��������� ������� ����� ����----------*/
		cursor.setPosition(static_cast<Vector2f>(Mouse::getPosition(menu))); // ��������� ������� �������

		menu.clear(Color(15, 14, 14));
		//������������� ���� �������� ������� �������������� �� �������
		border.setOutlineColor(Color(198, 36, 36));

		//������������� �������� ���������� �������
		cursor.setTexture(moveTexture);

		//������� ���������� ������ ����
		if (button1.catchButton(Mouse::getPosition(menu).x, Mouse::getPosition(menu).y))
		{
			cursor.setTexture(selectTexture);
			indexMenu = 0;
		}
		else if (button2.catchButton(Mouse::getPosition(menu).x, Mouse::getPosition(menu).y))
		{
			cursor.setTexture(selectTexture);
			indexMenu = 1;
		}
		else if (button3.catchButton(Mouse::getPosition(menu).x, Mouse::getPosition(menu).y))
		{
			indexMenu = 2;
			cursor.setTexture(selectTexture);
		}
		else {
			indexMenu = -1;
		}


		switch (indexMenu)
		{
		case -1:
			border.setOutlineColor(Color(15, 14, 14));
			break;
		case 0:
			//������� (x,y), ���������� (x,y)
			border = Border::printBorder(220, 60, 190, 200);
			break;
		case 1:
			border = Border::printBorder(270, 60, 170, 270);
			break;
		case 2:
			border = Border::printBorder(220, 60, 195, 340);
			break;
		}

		menu.setView(fixed);

		menu.draw(border); //������ �����
		menu.draw(Print::printText(L"��������", 98, 40, 50)); //������ ������, ����������
		menu.draw(Print::printText(L"������", 45, 225.0, 200));
		menu.draw(Print::printText(L"�������", 45, 200.0, 270));
		menu.draw(Print::printText(L"�����", 45, 225.0, 340));

		menu.draw(cursor); //������ ������

		menu.display();
	}
}