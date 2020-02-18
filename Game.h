#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace  sf;
using namespace  std;

//Цвета для рисования линий интерфейса
const Color RED = Color(198, 36, 36);
const Color BLACK = Color(15, 14, 14);
//Цвета для рисования ящиков
const Color YELLOW = Color(246, 181, 59);
const Color GREEN = Color(41, 157, 57);
const Color ORANGE = Color(196, 100, 23);
const Color REDD = Color(232, 88, 63);

//Точка отсчета для игрового поля
const int x = 60, y = 100;

//Рекорды по очкам загруженные из файла сохранения (инициализация массивов)
string records[10] = { "", "", "", "", "", "", "", "", "", "" };
int scoreRecords[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

//Функция сохранения нового рекорда
void saveScore(int score)
{
	int scoreBuff[11];
	for (int i = 0; i < 11; i++)
	{
		if (i < 10) { scoreBuff[i] = scoreRecords[i]; }
		if (i == 10) { scoreBuff[10] = score; }
	}

	for (int i = 0; i < 11; ++i)
	{
		cout << scoreBuff[i] << " ";
	}

	//Сортировка массива
	for (int i = 1; i < 11; ++i)
	{
		for (int r = 0; r < 11 - i; r++)
		{
			if (scoreBuff[r] < scoreBuff[r + 1])
			{
				//Обмен местами
				int temp = scoreBuff[r];
				scoreBuff[r] = scoreBuff[r + 1];
				scoreBuff[r + 1] = temp;
			}
		}
	}

	for (int i = 0; i < 11; ++i)
	{
		cout << scoreBuff[i] << " ";
	}

	ofstream file;
	file.open("Data/record.txt");
	if (file.is_open())
	{
		for (int i = 0; i < 10; i++)
		{
			file << scoreBuff[i] << "\n";
		}
	}

	file.close();
}


class Game
{
public:
	static void Display(RenderWindow &game, RenderWindow &menu)
	{
		ContextSettings settings;
		settings.antialiasingLevel = 8;
		Print::setFont("Data/font.otf");
		game.create(VideoMode(600, 800), "Arcanoid", Style::Titlebar, settings);
		game.setFramerateLimit(120); //Лимит частоты кадров

		/*-----------------Работа с курсором----------------*/
		game.setMouseCursorVisible(false);
		View fixed = game.getView();


		Texture moveTexture, selectTexture;
		moveTexture.loadFromFile("Data/Move.png"); //Курсор при движение
		selectTexture.loadFromFile("Data/Select.png"); //Курсор когда появляется возможность выбрать
		Sprite cursor(moveTexture);

		/*-----------------Отрисовка интерфейса----------------*/
		RectangleShape borderGame = Border::printBorder(480, 600, 60, 100);

		RectangleShape borderPlay = Border::printBorder(118, 60, 60, 720); //Кнопка Play
		RectangleShape borderAgain = Border::printBorder(110, 60, 200, 720); //Кнопка Заново
		RectangleShape borderButton = Border::printBorder(210, 60, 330, 720); //Кнопка Меню

		Object playBtn(40, 40, 92, 725);
		Object againBtn(45, 45, 225, 725);
		Object menuBtn(135, 30, 370, 735);

		/*-------------------Элементы игры--------------------*/
		//Платформа, шар и ящики
		Object gameSpace(480, 600, 60, 100);

		//Описание противников
		Color colors[4] = { REDD, ORANGE, GREEN, YELLOW };

		RectangleShape **vragMass = new RectangleShape*[4];
		Object **vragObject = new Object*[4];

		for (int i = 0; i < 4; i++)
		{
			vragMass[i] = new RectangleShape[5];
			vragObject[i] = new Object[5];
		}

		for (int i = 0; i < 4; i++)
		{
			int n = 0;
			for (int j = 0; j < 5; j++)
			{
				vragMass[i][j] = Border::printBorder(80, 20, 80 + n * 90, 120 + i * 35);
				vragObject[i][j] = Object(80, 20, 80 + n * 90, 120 + i * 35, colors[i]);
				n++;
				vragMass[i][j].setFillColor(colors[i]);
				vragMass[i][j].setOutlineThickness(0);
			}
		}

		RectangleShape playerShape = Border::printBorder(100, 10, x + 190, y + 580);
		playerShape.setFillColor(Color::White);
		playerShape.setOutlineThickness(0);
		Object player(100, 10, x + 190, y + 580);

		//Описание игрового шара
		CircleShape ballShape(10);

		ballShape.setFillColor(Color(28, 45, 155));
		ballShape.setOutlineThickness(0);
		ballShape.setPointCount(300);

		ballShape.setPosition(290, y + 410);
		Object ball(20, 20, 290, y + 420);

		//Индекс выделеной кнопки
		int indexMenu = -1;

		/*----------Работа с картинками для кнопок----------*/
		Image image1, image2, image3;
		Texture texture1, texture2, texture3;
		Sprite spritePlay, spriteAgain;
		spritePlay.setPosition(100, 728);
		spriteAgain.setPosition(235, 728);

		image1.loadFromFile("Data/play.png");
		image2.loadFromFile("Data/pause.png");
		image3.loadFromFile("Data/again.png");
		texture1.loadFromImage(image2);
		texture2.loadFromImage(image1);
		texture3.loadFromImage(image3);

		spritePlay.setTexture(texture2);
		spriteAgain.setTexture(texture3);

		/*-----------------Отрисовка жизней----------------*/
		CircleShape life[3];
		life[0].setRadius(8);
		life[0].setFillColor(RED);
		life[0].setOutlineThickness(3);
		life[0].setOutlineColor(RED);
		life[0].setPosition(400, 40);

		life[1].setRadius(8);
		life[1].setFillColor(RED);
		life[1].setOutlineThickness(3);
		life[1].setOutlineColor(RED);
		life[1].setPosition(450, 40);

		life[2].setRadius(8);
		life[2].setFillColor(RED);
		life[2].setOutlineThickness(3);
		life[2].setOutlineColor(RED);
		life[2].setPosition(500, 40);

		//Флаг нажата ли пауза
		bool pause = false;
		//Нажата ли кнопка продолжить
		bool contun = false;
		//Нажата ли кнопка начать
		bool start = false;

		//Закончились ли жизни 
		bool gameOver = false;

		Clock clock;

		//Скорость перемещения по x и y
		int speedGame = 4;
		int dx = 0, dy = speedGame, nx = 1, ny = 1;
		int score = 0, bonus = 0;

		//Количество жизней
		int lifeCount = 3;
		int countVrag = 20;

		ifstream file("Data/record.txt");

		if (file.is_open())
		{
			int i = 0;

			while (!file.eof())
			{
				getline(file, records[i]);
				if (i < 9) { i++; }
				else { break; }
			}
		}
		file.close();


		for (int i = 0; i < 10; i++)
		{
			scoreRecords[i] = stoi(records[i]);
		}

		while (game.isOpen())
		{
			Event event;

			//Получаем 120 кадров в секунду
			float time = clock.getElapsedTime().asMilliseconds();
			if (time >= 4.2)
			{
				clock.restart();

				if (ballShape.getPosition().y + 20 >= 700)
				{
					lifeCount -= 1;
					switch (lifeCount)
					{
					case 2:
						life[2].setFillColor(BLACK);
						ballShape.setPosition(290, y + 410);
						ny = -1;
						dx = 0;
						pause = true;
						contun = true;
						break;
					case 1:
						life[1].setFillColor(BLACK);
						ballShape.setPosition(290, y + 410);
						ny = -1;
						dx = 0;
						pause = true;
						contun = true;
						break;
					case 0:
						life[0].setFillColor(BLACK);
						ballShape.setFillColor(BLACK);
						ballShape.setPosition(0, 0);
						pause = true;
						contun = true;
						gameOver = true;
						saveScore(score);
						break;
					}
					//ny = -ny;
					//dy = ny * dy;
				}

				/*----------Обрабтка столкновений с границей игровой области----------*/
				if (ballShape.getPosition().y <= 100)
				{
					ny = -ny;
					dy = ny * dy;
				}

				if (ballShape.getPosition().x <= 60)
				{
					nx = -nx;
					dx = nx * dx;
				}

				if (ballShape.getPosition().x + 20 >= 540)
				{
					nx = -nx;
					dx = nx * dx;
				}

				/*------------------Обработка столкновений с ракеткой------------------*/
				//Мячик попал на ракетку
				if ((ball.x3 + 10 >= player.x1) && (ball.x3 + 10 <= player.x2) && (ball.y3 >= player.y1))
				{
					bonus = 1;
					//Мячик попал на левым край ракетки
					if ((ball.x3 + 10 >= player.x1) && (ball.x3 + 10 <= player.x1 + 10))
					{
						ny = -ny;
						dy = ny * dy;

						dx = -1 * fabs(dy);
						dx = nx * dx;
					}
					//Мячик попал на правый край ракетки
					if ((ball.x3 + 10 >= player.x2 - 10) && (ball.x2 + 10 >= player.x2))
					{
						ny = -ny;
						dy = ny * dy;

						dx = fabs(dy);
						dx = nx * dx;
					}

					//Мячик попал на основную часть ракетки
					if (((ball.x3 + 10 >= player.x1 + 11) && (ball.x3 + 10 <= player.x1 + 41)) ||
						((ball.x3 + 10 >= player.x1 + 51) && (ball.x3 + 10 <= player.x1 + 81)))
					{
						ny = -ny;
						dy = ny * dy;

						dx = fabs(dy) - 2;
						dx = nx * dx;
					}

					//Мячик попал в середину ракетки
					if (((ball.x3 + 10 >= player.x1 + 42) && (ball.x3 + 10 <= player.x1 + 62)))
					{
						ny = -ny;
						dy = ny * dy;
						dx = 0;
					}
				}

				if (start)
				{
					//Перемещаем шарик
					if (!pause) { ballShape.move(dx, dy); }
					ball.update(ballShape.getPosition());
					if (dx == 0) { dx = fabs(dx); }
				}
			}

			//Нажата A или Left
			if ((Keyboard::isKeyPressed(Keyboard::A)) || ((Keyboard::isKeyPressed(Keyboard::Left))))
			{
				if (player.x3 - 7 > gameSpace.x3)
				{
					playerShape.move(-7, 0);
					player.update(playerShape.getPosition());
				}
			}
			//Нажата D или Right
			if ((Keyboard::isKeyPressed(Keyboard::D)) || ((Keyboard::isKeyPressed(Keyboard::Right))))
			{
				if (player.x2 + 7 < gameSpace.x4)
				{
					playerShape.move(7, 0);
					player.update(playerShape.getPosition());
				}
			}

			while (game.pollEvent(event))
			{
				switch (event.type)
				{
				case Event::KeyPressed:

					//Нажата Enter
					if (Keyboard::isKeyPressed(Keyboard::Return))
					{
						menu.setVisible(true);
						game.close();
					}
					//Нажата Space
					if (Keyboard::isKeyPressed(Keyboard::Space))
					{
						if (start == false)
						{
							spritePlay.setTexture(texture1);
							start = true;
						}
						else
						{
							if (pause == true)
							{
								spritePlay.setTexture(texture1);
								pause = false;
							}
							else
							{
								spritePlay.setTexture(texture2);
								pause = true;
							}
							contun = false;
						}
					}
					break;
				case Event::MouseButtonReleased:
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						if (playBtn.catchButton(Mouse::getPosition(game).x, Mouse::getPosition(game).y))
						{
							if (start == false)
							{
								spritePlay.setTexture(texture1);
								start = true;
							}
							else
							{
								if (pause == true)
								{
									spritePlay.setTexture(texture1);
									pause = false;
								}
								else
								{
									spritePlay.setTexture(texture2);
									pause = true;
								}
								contun = false;
							}
						}
						if (againBtn.catchButton(Mouse::getPosition(game).x, Mouse::getPosition(game).y))
						{
							Border::restart = true; //Поднимаем флаг нажатия кнопки рестарт
							//menu.setVisible(true);
							game.close(); //Закрываем окно с игрой дял перезапуска

						}
						if (menuBtn.catchButton(Mouse::getPosition(game).x, Mouse::getPosition(game).y))
						{
							menu.setVisible(true);
							game.close();
						}
					}
					break;
				}
			}

			cursor.setPosition(static_cast<Vector2f>(Mouse::getPosition(menu))); // Установка позиции курсора
			//Устанавливаем текстуру двигаюшего курсора
			cursor.setTexture(moveTexture);

			//Обводка выбранного пункта меню
			if (playBtn.catchButton(Mouse::getPosition(game).x, Mouse::getPosition(game).y))
			{
				cursor.setTexture(selectTexture);
				indexMenu = 0;
			}
			else if (againBtn.catchButton(Mouse::getPosition(game).x, Mouse::getPosition(game).y))
			{
				cursor.setTexture(selectTexture);
				indexMenu = 1;
			}
			else if (menuBtn.catchButton(Mouse::getPosition(game).x, Mouse::getPosition(game).y))
			{
				cursor.setTexture(selectTexture);
				indexMenu = 2;
			}
			else { indexMenu = -1; }


			switch (indexMenu)
			{
			case -1:
				borderPlay.setOutlineColor(BLACK);
				borderAgain.setOutlineColor(BLACK);
				borderButton.setOutlineColor(BLACK);
				break;
			case 0:
				//Устанавливаем цвет внешнего контура прямоугольника на красный
				borderPlay.setOutlineColor(RED);
				break;
			case 1:
				borderAgain.setOutlineColor(RED);
				break;
			case 2:
				borderButton.setOutlineColor(RED);
				break;
			}

			game.clear(Color(15, 14, 14));

			game.draw(Print::printText(L"Очки: " + to_wstring(score), 50, 75, 15));
			//game.draw(Print::printText(to_wstring(i), 50, 75, 15)); to_wstring(i) число в wstring 
			//Отрисовка жизни
			game.draw(life[0]);
			game.draw(life[1]);
			game.draw(life[2]);

			game.draw(borderButton);
			game.draw(Print::printText(L"Меню", 45, 370, 720));

			//Рисуем рамки
			game.draw(borderGame);

			game.draw(borderPlay);
			game.draw(spritePlay);

			game.draw(borderAgain);
			game.draw(spriteAgain);

			//Отрисовка игрока и ящиков
			game.draw(playerShape);
			game.draw(ballShape);

			if (start == false)
			{
				game.draw(Print::printText(L"НАЧАТЬ ИГРУ", 50, 150, 350));
			}
			else
			{
				if (countVrag == 0)
				{
					game.draw(Print::printText(L"ВЫ ВЫЙГРАЛИ", 45, 135, 350));
					dx = 0;
					dy = 0;
					ballShape.setFillColor(BLACK);
					//saveScore(score);
				}
				else
				{
					if (!gameOver)
					{
						//Отрисовка надписи о паузе
						if (contun)
						{
							spritePlay.setTexture(texture2);
							game.draw(Print::printText(L"ВОЗОБНОВИТЬ ИГРУ", 42, 100, 350));
						}
						else
						{
							if (pause) 
							{ 
								game.draw(Print::printText(L"ПАУЗА", 60, 215, 350)); 
								dx = 0;
							}
						}
					}
					else
					{
						game.draw(Print::printText(L"ИГРА ОКОНЧЕНА", 45, 135, 350));
					}
				}
			}

			/*--------------------Обрабтка столкновений с врагами-----------------*/
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					if ((vragObject[i][j].catchButton(ball.x1 + 10, ball.y1)) && (vragObject[i][j].live == true))
					{
						vragObject[i][j].live = false;
						int k = 1;
						//Подсчет очков
						if (bonus == 2) { k = 2; }
						if (bonus == 4) { k = 4; bonus = 0; }

						if (vragObject[i][j].color == colors[0]) { score = (score + 7) * k; }
						if (vragObject[i][j].color == colors[1]) { score = (score + 5) * k; }
						if (vragObject[i][j].color == colors[2]) { score = (score + 3) * k; }
						if (vragObject[i][j].color == colors[3]) { score = (score + 1) * k; }
						--countVrag;
						dy = -dy;;
						bonus++;
					}
				}
			}

			//Отрисовка ящиков
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					if (vragObject[i][j].live == true) { game.draw(vragMass[i][j]); }
				}
			}

			//Отрисовка курсора
			game.draw(cursor);

			game.display();
		}
	}

};