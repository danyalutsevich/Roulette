
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <conio.h>
#include <ctime>
#include <string>


using namespace std;
using namespace sf;

int main()
{
	srand(time(0));

	RenderWindow Window(VideoMode(640 * 2, 480 * 2, 32), "Roulette");


	Texture TnumberBackground;
	TnumberBackground.loadFromFile("numberBackground.png");

	RectangleShape numberBackground(Vector2f(70, 40));
	numberBackground.setTexture(&TnumberBackground, true);


	Image icon;
	icon.loadFromFile("2.png");
	Window.setIcon(512, 512, icon.getPixelsPtr());

	RectangleShape pointer(Vector2f(75, 75));
	Texture Tpointer;


	Tpointer.loadFromFile("pointer.png");
	pointer.setTexture(&Tpointer, true);

	pointer.setPosition(164, 10);

	RectangleShape rect(Vector2f(400, 400));
	rect.setRotation(356);


	Texture roulette;



	if (!roulette.loadFromFile("2.png")) {
		cout << "Could not load texture\n";

	}

	rect.setPosition(200, 250);

	rect.setTexture(&roulette, true);

	int rouletteNumbers[15][5]{

		0,0,0,49,0,
		39,41,1,2,3,
		0,0,4,5,6,
		47,0,7,8,9,
		0,0,10,11,12,
		37,42,13,14,15,
		0,0,16,17,18,
		38,0,19,20,21,
		0,0,22,23,24,
		48,43,25,26,27,
		0,0,28,29,30,
		40,0,31,32,33,
		0,0,34,35,36,
		50,56,44,45,46,
		51,52,53,54,55

	};

	int height = 60;
	int width = 130;

	Font font;
	font.loadFromFile("Tomato Regular.ttf");

	Text text;

	text.setFont(font);

	bool mapFlag = true;
	bool flag = true;
	float rotation = 0;
	int num = 0;
	int bet = 0;
	rect.setOrigin(100 * 2, 100 * 2);
	int numbers[37] = { 0,32,15,19,4,21,2,25,17,34,6,27,13,36,11,30,8,23,10,5,24,16,33,1,20,14,31,9,22,18,29,7,28,12,35,3,26 };
	int index = 0;


	int red[18]{ 1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36 };

	int black[18]{ 2,4,6,8,10,11,13,15,17,20,22,24,26,28,29,31,33,35 };

	int betHeight = 800;
	int betWidth = 10;
	int betMargin = 90;
	int previousMargin = 70;


	bool outOfTable = false;
	bool mouseFlag = false;
	bool displayFlag = false;
	Texture TBetOne;
	TBetOne.loadFromFile("BetOne.png");

	Texture TBetFive;
	TBetFive.loadFromFile("BetFive.png");

	Texture TBetTwentyFive;
	TBetTwentyFive.loadFromFile("BetTwentyFive.png");

	Texture TBetFifty;
	TBetFifty.loadFromFile("BetFifty.png");

	Texture TBetHundred;
	TBetHundred.loadFromFile("BetHundred.png");


	int bets[200]{ 0 };
	int betsAmount[200]{ 0 };
	int betsCounter = 0;
	int betAmount = 0;

	RectangleShape chipShape(Vector2f(25, 25));

	RectangleShape betBackground(Vector2f(75, 75));

	RectangleShape mesh(Vector2f(width, height));
	mesh.setOutlineColor(Color(255, 255, 255));
	mesh.setFillColor(Color(51, 101, 77));
	mesh.setOutlineThickness(1);

	Vector2i mousePos;
	Vector2i mouseBetPos;
	Vector2i chipPos[200];
	Mouse mouse;
	mouse.isButtonPressed(Mouse::Left);
	Window.setFramerateLimit(100);



	RectangleShape Previos(Vector2f(70, 40));
	Previos.setTexture(&TnumberBackground, true);

	int balance = 1000;
	bool matchflag = false;
	Text Tbalance;
	Tbalance.setFont(font);
	Tbalance.setPosition(Vector2f(50, 450));
	string BALANCE = "Balance : ";

	int PreviousNumbers[200];
	int PreviousNumbersCount = 0;

	while (balance) {

		mousePos = Mouse::getPosition(Window);

		Event Event;

		displayFlag = false;;

		if (Event::MouseMoved) {

			displayFlag = true;

		}


		if (flag) {

			system("cls");

			cout << "\n";
			cout << "Index: " << index << "\n";

			cout << "Rotation: ";
			cout << rect.getRotation() << "\n";
			cout << "Rotation formula : ";
			cout << (int)(360 - ((index) * (360. / 37.))) - 3 << "\n";
			cout << "num: ";
			cout << rotation / 9.72;
			cout << "\n";
			cout << "Num: ";
			cout << num << "\n";
			cout << "Bet " << bet << "\n";
			cout << "Mouse pos X " << mousePos.x << "Y " << mousePos.y << "\n";
			cout << "Bet Amount: " << betAmount << "\n";
			cout << "X " << (mousePos.x - 470) / width << "Y " << (mousePos.y - 30) / height << "\n";
			cout << "Bet Amount: " << betAmount << "\n";
			cout << "Balance: " << balance << "\n";


			for (int i = PreviousNumbersCount-1; i >= 0; i--) {

				cout << "P " << PreviousNumbers[i] << "\n";
			}

			for (int i = 0; i < betsCounter; i++) {

				cout << "Bet: " << bets[i] << "\n";
				cout << "Bet Amount: " << betsAmount[i] << "\n";

			}


			flag = false;
		}

		outOfTable = false;
		
		if (mousePos.x > 470 && mousePos.y > 30 && mousePos.x < 1120 && mousePos.y < 870) {
			mouseBetPos.x = (mousePos.x - 470) / width;
			mouseBetPos.y = (mousePos.y - 30) / height;
		}
		else {
			outOfTable = true;
		}

		if (mouseBetPos.x >= 0 && mouseBetPos.x < 5 && mouseBetPos.y >= 0 && mouseBetPos.y < 14 && rouletteNumbers[mouseBetPos.y][mouseBetPos.x]) {
			bet = rouletteNumbers[mouseBetPos.y][mouseBetPos.x];
		}
		else {
			bet = 0;
		}

		if (bet == 0 && mouseBetPos.y > 0) {

			for (int i = 0; i < 4; i++) {

				if (bet == 0) {
					bet = rouletteNumbers[mouseBetPos.y - i][mouseBetPos.x];
				}

			}

		}

		while (Window.pollEvent(Event)) {

			switch (Event.type) {


			case Event::Closed:

				Window.close();
				break;
			case Event::KeyPressed:

				if (Event.key.code == sf::Keyboard::P) {


					for (int i = 0; i < 37; i++) {

						if (num == numbers[i]) {

							index = i;

						}

					}


				}
				else if (Event.key.code == sf::Keyboard::S) {
					num = rand() % 37;

					PreviousNumbers[PreviousNumbersCount] = num;
					PreviousNumbersCount++;

					for (int i = 0; i < 37; i++) {

						if (num == numbers[i]) {

							index = i;

						}

					}

					for (int i = 0; i < 90; i++) {

						rect.rotate(i);

						Window.draw(rect);
						Window.display();

						Sleep(i / 2);

					}
				

						rect.setRotation((int)(360 - ((index) * (360. / 37.))) + 40);

					for (int i = 1; i < 90; i++) {

						rect.rotate(89 - i);

						Window.draw(rect);
						Window.display();

						Sleep(i / 2);


					}




					for (int i = 0; i <= betsCounter; i++) {
						cout << "CHECKING";
						if (bets[i] == num && bets[i] > 0 && bets[i] < 37) {

							balance += betsAmount[i] * 35;

						}

						else if (bets[i] == 37) {

							matchflag = 0;
							for (int i = 0; i < 18; i++) {

								if (num == red[i]) {
									matchflag = 1;

								}


							}

							if (matchflag) {

								balance += betsAmount[i];

							}

							else {

								balance -= betsAmount[i];

							}
						}

						else if (bets[i] == 38) {

							matchflag = 0;
							for (int i = 0; i < 18; i++) {

								if (num == black[i]) {
									matchflag = 1;

								}


							}

							if (matchflag) {

								balance += betsAmount[i];

							}

							else {

								balance -= betsAmount[i];

							}
						}

						else if (bets[i] == 39 && num > 0 && num < 19) {

							balance += betsAmount[i];

						}

						else if (bets[i] == 40 && num > 18 && num < 37) {

							balance += betsAmount[i];

						}

						else if (bets[i] == 41 && num > 0 && num < 13) {

							balance += betsAmount[i] * 2;

						}

						else if (bets[i] == 42 && num > 12 && num < 25) {

							balance += betsAmount[i] * 2;

						}

						else if (bets[i] == 43 && num > 24 && num < 37) {

							balance += betsAmount[i] * 2;

						}

						else if (bets[i] == 44) {
							matchflag = 0;
							for (int i = 1; i <= 34; i += 3) {

								if (num == i) {

									matchflag = 1;

								}

							}


							if (matchflag) {

								balance += betsAmount[i];

							}

							else {

								balance -= betsAmount[i];

							}


						}

						else if (bets[i] == 45) {
							matchflag = 0;
							for (int i = 2; i <= 35; i += 3) {

								if (num == i) {

									matchflag = 1;

								}

							}


							if (matchflag) {

								balance += betsAmount[i];

							}

							else {

								balance -= betsAmount[i];

							}


						}

						else if (bets[i] == 46) {
							matchflag = 0;
							for (int i = 3; i <= 36; i += 3) {

								if (num == i) {

									matchflag = 1;

								}

							}


							if (matchflag) {

								balance += betsAmount[i];

							}

							else {

								balance -= betsAmount[i];

							}


						}

						else if (bets[i] == 47 && num % 2 == 0) {

							balance += betsAmount[i];

						}

						else if (bets[i] == 48 && num % 2 == 1) {

							balance += betsAmount[i];

						}

						else if (bets[i] == 49 && num == 0) {

							balance += betsAmount[i] * 35;

						}
						else {

							balance -= betsAmount[i];

						}









					}
					for (int i = 0; i < betsCounter; i++) {
						bets[i] = 0;
						betsAmount[i] = 0;
					}

					betsCounter = 0;



					flag = true;

				}
				else if (Event.key.code == sf::Keyboard::Enter) {

				}
				else if (Event.key.code == sf::Keyboard::B) {

				}
				else if (Event.key.code == Mouse::Left) {

					betAmount = 0;

				}
				break;
			case Event::MouseButtonReleased:



				if (mousePos.y > 800 && mousePos.x > 370 && mousePos.x < 445 && mousePos.y < 875) {

					betAmount = 100;
				}
				else if (mousePos.y > 800 && mousePos.x > 280 && mousePos.x < 445 && mousePos.y < 875) {

					betAmount = 50;
				}
				else if (mousePos.y > 800 && mousePos.x > 190 && mousePos.x < 445 && mousePos.y < 875) {

					betAmount = 25;
				}
				else if (mousePos.y > 800 && mousePos.x > 100 && mousePos.x < 445 && mousePos.y < 875) {

					betAmount = 5;
				}
				else if (mousePos.y > 800 && mousePos.x > 10 && mousePos.x < 445 && mousePos.y < 875) {

					betAmount = 1;
				}
				

				chipPos[betsCounter].x = mouseBetPos.x;
				chipPos[betsCounter].y = mouseBetPos.y;
				if (mousePos.x >= 470) {

					bets[betsCounter] = bet;
					betsAmount[betsCounter] = betAmount;
					betsCounter++;
					mapFlag = true;
					flag = true;

				}

				break;

			}

			//370 280 190 100 10









		}

		Window.clear(Color(51, 101, 77));



		for (int y = 0; y < 15; y++) {

			for (int x = 0; x < 5; x++) {

				for (int i = 0; i < 18; i++) {

					if (rouletteNumbers[y][x] == red[i]) {
						numberBackground.setFillColor(Color(255, 0, 0));

					}
					if (rouletteNumbers[y][x] == black[i]) {
						numberBackground.setFillColor(Color(0, 0, 0));

					}

				}


				if (rouletteNumbers[y][x] < 10 || rouletteNumbers[y][x] == 49) {

					text.setPosition(Vector2f(x * width + 500 + 24, y * height + 40));

				}
				else if (rouletteNumbers[y][x] <= 21) {
					text.setPosition(Vector2f(x * width + 500 + 18, y * height + 40));

				}
				else if (rouletteNumbers[y][x] == 41 || rouletteNumbers[y][x] == 42 || rouletteNumbers[y][x] == 43) {
					mesh.setScale(Vector2f(1, 4));
					//mesh.setOutlineThickness(0.25);
				}
				else if (rouletteNumbers[y][x] == 44 || rouletteNumbers[y][x] == 45 || rouletteNumbers[y][x] == 46) {
					mesh.setScale(Vector2f(1, 1));
					text.setPosition(Vector2f(x * width + 500 + 12, y * height + 40));
					//mesh.setOutlineThickness(1);
				}
				else {
					mesh.setScale(Vector2f(1, 2));
				//	mesh.setOutlineThickness(1);
					text.setPosition(Vector2f(x * width + 500 + 12, y * height + 40));

				}

				if (rouletteNumbers[y][x] > 36 && rouletteNumbers[y][x] != 49) {
					mesh.setFillColor(Color(51, 101, 77));

					text.setRotation(90);
					//text.setPosition(text.getPosition() + Vector2f(45, 15));
					text.setPosition(Vector2f(x * width + 500, y * height + 40));
					numberBackground.setFillColor(Color::Transparent);
				}

				numberBackground.setPosition(x * width + 500, y * height + 40);
				mesh.setPosition(x * width + 470, y * height + 30 + 1);


				/*for (int i = 0; i < 38; i++) {

					if (betsAmount[i] == 1) {
						chipShape.setTexture(&TBetOne, true);
					}
					else if (betsAmount[i] == 5) {
						chipShape.setTexture(&TBetFive, true);
					}
					else if (betsAmount[i] == 25) {
						chipShape.setTexture(&TBetTwentyFive, true);
					}
					else if (betsAmount[i] == 50) {
						chipShape.setTexture(&TBetFifty, true);
					}
					else if (betsAmount[i] == 100) {
						chipShape.setTexture(&TBetHundred, true);
					}

					if (bets[i] == rouletteNumbers[x][y]&&bets[i]!=0) {

						chipShape.setPosition(x* width + 500, y* height + 40);
						Window.draw(chipShape);
					}

				}*/


				if (rouletteNumbers[y][x] == 37) {

					numberBackground.setFillColor(Color::Transparent);
					text.setString("");
					mesh.setFillColor(Color(255, 0, 0));


				}
				else if (rouletteNumbers[y][x] == 38) {

					numberBackground.setFillColor(Color::Transparent);
					text.setString("");
					mesh.setFillColor(Color(0, 0, 0));


				}
				else if (rouletteNumbers[y][x] == 39) {
					mesh.setFillColor(Color(51, 101, 77));

					text.setRotation(90);
					//text.setPosition(text.getPosition() + Vector2f(45, 15));
					text.setPosition(Vector2f(x * width + 500 + 50, y * height + 40 + 20));
					text.setString("1-18");
					numberBackground.setFillColor(Color::Transparent);

				}
				else if (rouletteNumbers[y][x] == 40) {

					text.setString("19-36");
					text.setPosition(Vector2f(x * width + 500 + 50, y * height + 40));
					mesh.setFillColor(Color(51, 101, 77));
					numberBackground.setFillColor(Color::Transparent);
				}
				else if (rouletteNumbers[y][x] == 41) {
					text.setRotation(90);
					text.setString("1st 12");
					text.setPosition(Vector2f(x * width + 500 + 50, y * height + 40 + 50));
					numberBackground.setFillColor(Color::Transparent);

				}
				else if (rouletteNumbers[y][x] == 42) {
					text.setRotation(90);
					text.setString("2nd 12");
					text.setPosition(Vector2f(x * width + 500 + 50, y * height + 40 + 50));
					numberBackground.setFillColor(Color::Transparent);

				}
				else if (rouletteNumbers[y][x] == 43) {
					text.setRotation(90);
					text.setString("3rd 12");
					text.setPosition(Vector2f(x * width + 500 + 50, y * height + 40 + 50));
					numberBackground.setFillColor(Color::Transparent);

				}
				else if (rouletteNumbers[y][x] == 44) {

					text.setRotation(0);
					text.setString("1st");
					text.setPosition(Vector2f(x * width + 510, y * height + 40));
					numberBackground.setFillColor(Color::Transparent);

				}
				else if (rouletteNumbers[y][x] == 45) {

					text.setRotation(0);
					text.setString("2nd");
					text.setPosition(Vector2f(x * width + 500, y * height + 40));
					numberBackground.setFillColor(Color::Transparent);

				}
				else if (rouletteNumbers[y][x] == 46) {

					text.setRotation(0);
					text.setString("3rd");
					text.setPosition(Vector2f(x * width + 500, y * height + 40));
					numberBackground.setFillColor(Color::Transparent);

				}
				else if (rouletteNumbers[y][x] == 47) {

					text.setRotation(90);
					text.setString("even");
					text.setPosition(Vector2f(x * width + 500 + 50, y * height + 40));
					numberBackground.setFillColor(Color::Transparent);

				}
				else if (rouletteNumbers[y][x] == 48) {

					text.setRotation(90);
					text.setString("odd");
					text.setPosition(Vector2f(x * width + 500 + 50, y * height + 40 + 10));
					numberBackground.setFillColor(Color::Transparent);

				}
				else if (rouletteNumbers[y][x] == 49) {
					text.setString(to_string(0));
					numberBackground.setFillColor(Color(2, 170, 82));
					betBackground.setTexture(&TBetHundred, true);

				}
				else if (rouletteNumbers[y][x] == 51) {

					numberBackground.setFillColor(Color(255, 255, 255));
					betBackground.setTexture(&TBetOne, true);
					betBackground.setPosition(Vector2f(betWidth, betHeight));

				}
				else if (rouletteNumbers[y][x] == 52) {

					numberBackground.setFillColor(Color(255, 255, 255));
					betBackground.setTexture(&TBetFive, true);
					betBackground.setPosition(Vector2f(betWidth + betMargin * 1, betHeight));
				}
				else if (rouletteNumbers[y][x] == 53) {

					numberBackground.setFillColor(Color(255, 255, 255));
					betBackground.setTexture(&TBetTwentyFive, true);
					betBackground.setPosition(Vector2f(betWidth + betMargin * 2, betHeight));

				}
				else if (rouletteNumbers[y][x] == 54) {

					numberBackground.setFillColor(Color(255, 255, 255));
					betBackground.setTexture(&TBetFifty, true);
					betBackground.setPosition(Vector2f(betWidth + betMargin * 3, betHeight));

				}
				else if (rouletteNumbers[y][x] == 55) {

					numberBackground.setFillColor(Color(255, 255, 255));
					betBackground.setTexture(&TBetHundred, true);
					betBackground.setPosition(Vector2f(betWidth + betMargin * 4, betHeight));

				}
				else {

					numberBackground.setTexture(&TnumberBackground, true);
					text.setRotation(0);
					text.setString(to_string(rouletteNumbers[y][x]));
					mesh.setFillColor(Color(51, 101, 77));
					mesh.setOutlineColor(Color(255, 255, 255));

				}

				if (rouletteNumbers[y][x] == bet && !outOfTable) {
					mesh.setFillColor(Color(102, 202, 154));
				}



				/*if (rouletteNumbers[y][x] == 37) {

					text.setString("");
					mesh.setFillColor(Color(255, 0, 0));
					mesh.setOutlineColor(Color(255, 0, 0));

				}
				else if (rouletteNumbers[y][x] == 38) {

					text.setString("");
					mesh.setFillColor(Color(0, 0, 0));
					mesh.setOutlineColor(Color(0, 0, 0));

				}
				else if (rouletteNumbers[y][x] == 39) {
					mesh.setFillColor(Color::Transparent);
					text.setRotation(90);
					text.setString("1-18");
					numberBackground.setFillColor(Color::Transparent);

				}
				else if (rouletteNumbers[y][x] == 40) {

					text.setString("19-36");
					text.setPosition(Vector2f(x* width + 500, y* height + 40));
					numberBackground.setFillColor(Color::Transparent);

				}
				else if (rouletteNumbers[y][x] == 49) {

					text.setString(to_string(0));
				}

				else if (rouletteNumbers[y][x] == 51) {


					betBackground.setPosition(Vector2f(betWidth, betHeight));
				}
				else if (rouletteNumbers[y][x] == 52) {


					betBackground.setPosition(Vector2f(betWidth + betMargin * 1, betHeight));

				}
				else if (rouletteNumbers[y][x] == 53) {


					betBackground.setPosition(Vector2f(betWidth + betMargin * 2, betHeight));
				}
				else if (rouletteNumbers[y][x] == 54) {


					betBackground.setPosition(Vector2f(betWidth + betMargin * 3, betHeight));

				}
				else if (rouletteNumbers[y][x] == 55) {


					betBackground.setPosition(Vector2f(betWidth + betMargin * 4, betHeight));

				}
				else {
					text.setRotation(0);
					text.setString(to_string(rouletteNumbers[y][x]));
					mesh.setFillColor(Color(51, 101, 77));
					mesh.setOutlineColor(Color(255, 255, 255));
				}*/

				Window.draw(betBackground);

				if (rouletteNumbers[y][x] < 50 && rouletteNumbers[y][x] > 0) {

					Window.draw(mesh);
					Window.draw(numberBackground);
					Window.draw(text);

				}
				

				for (int i = 0; i < 200; i++) {

					if (betsAmount[i] == 1) {
						chipShape.setFillColor(Color::White);
						chipShape.setTexture(&TBetOne, true);
					}
					else if (betsAmount[i] == 5) {
						chipShape.setFillColor(Color::White);
						chipShape.setTexture(&TBetFive, true);
					}
					else if (betsAmount[i] == 25) {
						chipShape.setFillColor(Color::White);
						chipShape.setTexture(&TBetTwentyFive, true);
					}
					else if (betsAmount[i] == 50) {
						chipShape.setFillColor(Color::White);
						chipShape.setTexture(&TBetFifty, true);
					}
					else if (betsAmount[i] == 100) {
						chipShape.setFillColor(Color::White);
						chipShape.setTexture(&TBetHundred, true);
					}
					else {

						chipShape.setFillColor(Color::Transparent);

					}


					//if (rouletteNumbers[chipPos[i].y][chipPos[i].x] != 0 && bets[i] != 0) {

					chipShape.setPosition(chipPos[i].x * width + 520, chipPos[i].y * height + 50);

					Window.draw(chipShape);
					//}



				}
			}



		}


		for (int i = PreviousNumbersCount-1; i >= 0; i--) {

			for (int j = 0; j < 18; j++) {

				if (PreviousNumbers[i] == red[j]) {
					Previos.setFillColor(Color(255, 0, 0));

				}
				else if (PreviousNumbers[i] == black[j]) {
					Previos.setFillColor(Color(0, 0, 0));

				}
				else if (PreviousNumbers[i] == 0) {
					Previos.setFillColor(Color(2, 170, 82));


				}
			}
			text.setString(to_string(PreviousNumbers[i]));

			if (PreviousNumbers[i] < 10) {

			text.setPosition(Vector2f(1175+25, 60 + previousMargin * ((PreviousNumbersCount - 1) - i)));
			}
			else if (PreviousNumbers[i] < 20) {

				text.setPosition(Vector2f(1175 + 20, 60 + previousMargin * ((PreviousNumbersCount - 1) - i)));
			}
			else {
				text.setPosition(Vector2f(1175+15, 60 + previousMargin * ((PreviousNumbersCount - 1) - i)));

			}

			text.setRotation(0);
			Previos.setPosition(Vector2f(1175, 60 + previousMargin * ((PreviousNumbersCount - 1)-i)));

			Window.draw(Previos);
			Window.draw(text);
		}
		Tbalance.setString(BALANCE + to_string(balance));

		if (displayFlag) {

			Window.draw(rect);
			Window.draw(pointer);
			Window.draw(Tbalance);
			Window.display();
		}

		//system("cls");

	}

	Window.close();


}