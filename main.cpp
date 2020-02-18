#include <SFML/Graphics.hpp>
#include <string>
#include "Print.h"
#include "Border.h"
#include "Record.h"
#include "Game.h"

using namespace  sf;
using namespace  std;

Font Print::font; //Объявление статистического поля для дальнейшей инициализации
				  
bool Border::restart = false; //Флаг была ли нажата кнопка рестарт в окне игры

int main()
{
	RenderWindow menu, record, game;
	menu.create(VideoMode(600, 800), L"Арканоид", Style::Titlebar);
	//window.create(VideoMode(600, 800), "Arcanoid");
	menu.setFramerateLimit(60); //Лимит частоты кадров
	//menu.setMouseCursorVisible(false);
	menu.setActive(true);


	/*-------------Работа с курсором-------------*/
	menu.setMouseCursorVisible(false); //Скрываем системный курсор
	View fixed = menu.getView();

	//Загрузка значка курсора
	Texture moveTexture, selectTexture;
	moveTexture.loadFromFile("Data/Move.png"); //Курсор при движение
	selectTexture.loadFromFile("Data/Select.png"); //Курсор когда появляется возможность выбрать
	Sprite cursor(moveTexture);

	//Установка шрифта по умолчанию
	Print::setFont("Data/font.otf");
	//Размеры (x,y), координаты (x,y), тип(true - основная, false - маленькая)
	RectangleShape border;

	int indexMenu = -1; //Индекс выделеной кнопки

	Object button1(155, 30, 225, 215), button2(210, 30, 200, 285), button3(160, 30, 225, 355);


	while (menu.isOpen())
	{
		
		//Была ли нажата кнопка рестарт в окне Game
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
					//Нажата кнопка Играть
					if (button1.catchButton(Mouse::getPosition(menu).x, Mouse::getPosition(menu).y))
					{
						menu.setVisible(false);
						Game::Display(game, menu);
					}

					//Нажата кнопка Рекорды
					if (button2.catchButton(Mouse::getPosition(menu).x, Mouse::getPosition(menu).y))
					{
						menu.setVisible(false);
						Record::Render(record, menu);
					}

					//Нажата кнопка Выход
					if (button3.catchButton(Mouse::getPosition(menu).x, Mouse::getPosition(menu).y))
					{
						menu.close();
					}
				}
				break;
			case Event::KeyPressed:

				//Нажата Enter (для управления клавишами и Enter)
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

		/*----------Отрисовка каждого кадра меню----------*/
		cursor.setPosition(static_cast<Vector2f>(Mouse::getPosition(menu))); // Установка позиции курсора

		menu.clear(Color(15, 14, 14));
		//Устанавливаем цвет внешнего контура прямоугольника на красный
		border.setOutlineColor(Color(198, 36, 36));

		//Устанавливаем текстуру двигаюшего курсора
		cursor.setTexture(moveTexture);

		//Обводка выбранного пункта меню
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
			//Размеры (x,y), координаты (x,y)
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

		menu.draw(border); //Рисуем рамку
		menu.draw(Print::printText(L"АРКАНОИД", 98, 40, 50)); //Размер шрифта, координаты
		menu.draw(Print::printText(L"Играть", 45, 225.0, 200));
		menu.draw(Print::printText(L"Рекорды", 45, 200.0, 270));
		menu.draw(Print::printText(L"Выход", 45, 225.0, 340));

		menu.draw(cursor); //Рисуем курсор

		menu.display();
	}
}