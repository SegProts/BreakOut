#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include "Object.h"

using namespace  sf;
using namespace  std;

class Record
{
public:
	static void Render(RenderWindow &record, RenderWindow &menu)
	{
		Print::setFont("Data/font.otf"); 
		record.create(VideoMode(600, 800), "Arcanoid", Style::Titlebar);
		record.setMouseCursorVisible(false);
		record.setFramerateLimit(60); //Лимит частоты кадров

		RectangleShape borderText = Border::printBorder(480, 570, 60, 105);
		RectangleShape borderButton;

		/*-------------Работа с курсором-------------*/
		record.setMouseCursorVisible(false);
		View fixed = record.getView();

		//Загрузка значка курсора
		Texture moveTexture, selectTexture;
		moveTexture.loadFromFile("Data/Move.png"); //Курсор при движение
		selectTexture.loadFromFile("Data/Select.png"); //Курсор когда появляется возможность выбрать
		Sprite cursor(moveTexture);
		
		ifstream file;
		file.open("Data/record.txt");

		string records[10];
		Object button1(150, 30, 225, 715);
		int indexMenu = -1;

		if (file.is_open())
		{
			int i = 0;

			while (!file.eof())
			{
				getline(file, records[i]);
				if (i <9) { i++; }
				else { break; }
			}
		}

		file.close();

		while (record.isOpen())
		{
			Event event;

			while (record.pollEvent(event))
			{
				switch (event.type)
				{
				case Event::Closed:
					menu.setVisible(true);
					record.close();
					break;
				case Event::MouseButtonReleased:
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						if (button1.catchButton(Mouse::getPosition(record).x, Mouse::getPosition(record).y))
						{
							menu.setVisible(true);
							record.close();
						}
					}
					break;
				case Event::KeyPressed:

					//Нажата Enter
					if (Keyboard::isKeyPressed(Keyboard::Return))
					{
						menu.setVisible(true);
						record.close();
					}
					break;
				}
			}

			cursor.setPosition(static_cast<Vector2f>(Mouse::getPosition(menu))); // Установка позиции курсора
				//Устанавливаем цвет внешнего контура прямоугольника на красный
			borderButton.setOutlineColor(Color(198, 36, 36));

			//Устанавливаем текстуру двигаюшего курсора
			cursor.setTexture(moveTexture);

			//Обводка выбранного пункта меню
			if (button1.catchButton(Mouse::getPosition(menu).x, Mouse::getPosition(menu).y))
			{
				cursor.setTexture(selectTexture);
				indexMenu = 0;
			}
			else
			{
				indexMenu = -1;
			}


			switch (indexMenu)
			{
			case -1:
				borderButton.setOutlineColor(Color(15, 14, 14));
				break;
			case 0:
				//Размеры (x,y), координаты (x,y)
				borderButton = Border::printBorder(220, 60, 190, 700);
				break;
			}

			record.clear(Color(15, 14, 14));

			record.draw(Print::printText(L"Таблица рекордов:", 45, 70.0, 30));

			//Рисуем рамки
			record.draw(borderText);
			record.draw(borderButton);


			record.draw(Print::printText(L"Назад", 45, 225.0, 700));

			float y = 120.0;

			std::locale locale;
			sf::String s;

			Print::setFont("Data/rec_font.otf");

			for (int i = 0; i < 10; i++)
			{
				s = String(records[i], locale);
				if (s != "0"){ record.draw(Print::printText(s, 30, 90, y)); }
				y += 55;
			}

			Print::setFont("Data/font.otf");
			record.draw(cursor);

			record.display();
		}
	}

};