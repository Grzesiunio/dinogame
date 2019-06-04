//Grzegorz Drozda

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<string>
#include<sstream>
#include<time.h>
#include"Menu.h"
#include<fstream>
#include<Windows.h>
using namespace sf;
using namespace std;
#define WIDTH 800
#define HEIGHT 500
class Position
{
public:
	int x;
	int y;
};
int b = 0;
int main()
{



	RenderWindow window(VideoMode(WIDTH, HEIGHT), "Metin2 Run");
	//Menu
	//Menu menu(window.getSize().x, window.getSize().y);

	window.setFramerateLimit(150);

	//dino
	Texture t1;
	Texture t2;
	t1.loadFromFile("images/postac v1.png");
	t2.loadFromFile("images/postac v2.png");

	Sprite dinoArr[2];
	dinoArr[0] = Sprite(t1);
	dinoArr[1] = Sprite(t2);

	static const int DINO_Y_BOTTOM = HEIGHT - t1.getSize().y;
	Position dinoPos;
	dinoPos.x = 50;
	dinoPos.y = DINO_Y_BOTTOM;
	//texture moving index 0 or 1
	int index = 0;
	float frame = 0.f;
	float frameSpeed = 0.5f;
	const int changeCount = 5;

	int gravity = 8;
	bool isJumping = false;
	bool isBottom = true;

	//tree
	Texture t3;
	t3.loadFromFile("images/metin.png");
	Sprite tree(t3);

	static const int TREE_Y_BOTTOM = HEIGHT - t3.getSize().y;
	Position treePos;
	treePos.x = WIDTH-20 ;
	treePos.y = TREE_Y_BOTTOM+10;

	 double treeSpeed = 3;

	 //music
	 Music music;

	 if (!music.openFromFile("audio/muzyka.ogg"))
	 {
		 cout << "Error" << endl;
	 }
	 music.play();
	 //sound
	 Sound sound;
	 SoundBuffer buffer;
	 if (!buffer.loadFromFile("audio/jumping.wav"))
	 {
		 cout << "Error" << endl;
	 }
	 
	 Sound sound1;
	 SoundBuffer rage;
	 if (!rage.loadFromFile("audio/rage.wav"))
	 {
		 cout << "Error" << endl;
	 }
	 sound1.setBuffer(rage);
	 
	 
	 //Score
	 int score = 0;
	 int highscore = 0;
	 Font arial;
	 arial.loadFromFile("font/arial.ttf");
	 
	 std::ostringstream ssScore;
	 ssScore << "Score: " << score;
	 

	 //font highscore
	 Text lblScore;
	 lblScore.setCharacterSize(30);
	 lblScore.setPosition({ 10,30 });
	 lblScore.setFont(arial);
	 lblScore.setString(ssScore.str());
	 

	 

	 //Background
	 Texture bground;
	 bground.loadFromFile("images/m1.jpg");
	 Sprite background(bground);
	 
	 //menu
	 cout << "Witaj w grze! W tej o to gierce dostepne sa dwa tryby gry: " << endl;
	 cout << "1) Komputer vs Komputer czyli proces symulacji" << endl;
	 cout << "2) Gracz steruje postacia" << endl;
	 cout << "Wybierz tryb gry wpisujac (1 lub 2) lub nacisnij ESC jesli chcesz opuscic rozgrywke" << endl;
	 cout << "Powodzenia !!!" << endl;
	 int game_mode=0;
	 cout << "Podaj tryb gry: ";
	 cin >> game_mode;
	 while (game_mode != 1 && game_mode != 2)
	 {
		 cout << "Podaj tryb gry jeszcze raz: ";
		 cin >> game_mode;
	 }
	 Sleep(3000);

	 
	 
	
	 

	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
		
			if(e.type == Event::Closed)
			{
				window.close();
			}
			
		}
		
		//logic.

		//dino jump.
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			if (isBottom && !isJumping)
			{
				//make jumping stage;
				isJumping = true;
				isBottom = false;
			}

		}

		//dino jump(up and down)
		if (isJumping)
		{
			dinoPos.y -= gravity;
		}
		else
		{
			dinoPos.y += gravity;
		}

		//dino jump limit, dino bottom limit.
		if (dinoPos.y >= DINO_Y_BOTTOM)
		{
			dinoPos.y = DINO_Y_BOTTOM;
			isBottom = true;
		}
		if (dinoPos.y <= DINO_Y_BOTTOM - 300)
		{
			isJumping = false;
		}

		//dino step.
		frame += frameSpeed;
		if (frame > changeCount)
		{
			frame -= changeCount;
			++index;
			if (index >= 2) { index = 0; }
		}

		//tree move.
		if (treePos.x <= 0)
		{
			treePos.x = WIDTH;
		}
		else
		{
			treePos.x -= treeSpeed;
		}

		//tree Position.
		tree.setPosition(treePos.x, treePos.y);

		//dino Position.
		dinoArr[index].setPosition(dinoPos.x, dinoPos.y);

		//collision
		double faster_and_faster = 0.0006;
		if (dinoArr[0].getGlobalBounds().intersects(tree.getGlobalBounds()) && dinoArr[1].getGlobalBounds().intersects(tree.getGlobalBounds()))
		{
			
			treeSpeed = 0;
			if (treeSpeed == 0 && b==0)
			{
				sound1.play();
			}
			gravity = 0;
			if (gravity = 0)
			{
				//cout << "Eszkiere" << endl;
			}
			b++;
		}
		else
		{
			// Score system
			if (dinoPos.x-treePos.x>1)
			{
				score++;
				ssScore.str("");
				ssScore << "Score " << score;
				lblScore.setString(ssScore.str());
				
			}
			//tree speed
			
			treeSpeed = treeSpeed + faster_and_faster;
			
		}
		//sound of jumping
		if (isJumping == true)
		{
			sound.setBuffer(buffer);
			sound.play();
		}
		
		//esc game
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}


		//Score saving and loading + highscore
		std::ostringstream sshighScore;
		sshighScore << "Highscore is: " << highscore;
		Text highScore;
		highScore.setCharacterSize(30);
		highScore.setPosition({ 550,15 });
		highScore.setFont(arial);
		highScore.setString(sshighScore.str());
		std::ifstream readFile;
		readFile.open("score/highscore.txt");
		if (readFile.is_open())
		{
			while (!readFile.eof())
			{
				readFile >> highscore;
			}
		}
		readFile.close();
		std::ofstream writeFile("score/highscore.txt");
		if (writeFile.is_open())
		{
			if (score > highscore)
			{
				highscore = score;
			}
			writeFile << highscore;
		}
		writeFile.close();

		//simulator
		if (treePos.x-35 <200+(faster_and_faster*50000)&&game_mode==1)
		{
			if (isBottom && !isJumping)
			{
				isJumping = true;
				isBottom = false;
			}
		}
		

		
		//draw.
		
		
		window.clear(Color::Cyan);
		window.draw(background);
		window.draw(lblScore);
		window.draw(highScore);
		window.draw(dinoArr[index]);
		window.draw(tree);
		window.display();

	}
	return 0;
}