// Pong.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include<iostream>
#include<time.h>
#include<conio.h>
#include <Windows.h>
using namespace std;

//0->6
enum Dir { STOP = 0, LEFT, UPLEFT, DOWNLEFT, RIGHT, UPRIGHT, DOWNRIGHT };

class Ball
{
private:
	int x, y;
	int originalX, originalY;
	Dir direction;
public:
	Ball(int posx, int posy)
	{
		originalX = posx;
		originalY = posy;
		x = posx;
		y = posy;
		direction = STOP;
	}
	void Reset()
	{
		direction = STOP;
		x = originalX;
		y = originalY;
	}
	void ChangeDirection(Dir newdir) { direction = newdir; }
	inline int GetX() { return x; }
	inline int GetY() { return y; }
	void randomDirection() { direction = (Dir)((rand() % 6) + 1); }
	inline Dir getDirection() { return direction; }
	void Move() {
		switch (direction)
		{
		case STOP: break;
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UPLEFT:
			x--;
			y--;
			break;
		case UPRIGHT:
			x++;
			y--;
			break;
		case DOWNLEFT:
			x--;
			y++;
			break;
		case DOWNRIGHT:
			x++;
			y++;
			break;
		}
	}
	//friend function is a returning function
	//it can make access to all element that class
	//the first element of parentesis is the outPut, the second element is the class
	friend ostream & operator<<(ostream & output, Ball b)
	{
		output << "Ball [" << b.x << "," << b.y << "][" << b.direction << "]" << endl;
		return output;
	}
};

class Padle
{
private:
	int x, y;
	int originalX, originalY;
public:
	Padle() { x = y = 0; }
	Padle(int posX, int PosY) :Padle()
	{
		originalX = posX;
		originalY = PosY;
		x = posX;
		y = PosY;
	}
	inline void Reset() { x = originalX; y = originalY; }
	inline int getX() { return x; }
	inline int getY() { return y; }
	inline void MoveUP() { y--; }
	inline void MoveDown() { y++; }
	friend ostream & operator<<(ostream & o, Padle p)
	{
		o << "Padle [" << p.x << "," << p.y << "]";
		return o;
	}
};

class GameManager
{
private:
	int width, height;
	int score1, score2;
	char up1, up2, down1, down2;
	bool quit;
	Ball *ball;
	Padle *player1;
	Padle *player2;
public:
	GameManager(int w, int h)
	{
		srand(time(NULL));
		quit = false;
		//input setting
		up1 = 'w', down1 = 's';
		up2 = 'i', down2 = 'k';
		//reset score
		score1 = score2 = 0;
		//size
		width = w, height = h;
		//create ball in the center
		ball = new Ball(w / 2, h / 2);
		//create players near borders
		player1 = new Padle(1, (h / 2) - 3);
		player2 = new Padle(w - 2, (h / 2) - 3);
	}
	~GameManager()
	{
		delete player1, player2, ball;
	}
	void scoreUp(Padle *player)
	{
		if (player == player1)
		{
			score1++;
		}
		else
		{
			score2++;
		}
		ball->Reset();
		player1->Reset();
		player2->Reset();
	}
	void Draw()
	{
		system("cls");
		//up wall
		for (int i = 0; i < width + 2; i++)
		{
			cout << "\xB2";
		}
		cout << endl;
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width + 2; j++)
			{
				//ball position
				int ballx = ball->GetX();
				int bally = ball->GetY();
				//players positions
				int player1x = player1->getX();
				int player1y = player1->getY();
				int player2x = player2->getX();
				int player2y = player2->getY();
				//draw wall
				if (j == 0 || j == width)
				{
					cout << "\xB2";
				}
				//draw ball
				if (j == ballx && i == bally)
				{
					cout << "o";
				}
				//draw 3 segment of player
				else if (player1x == j && (player1y == i || player1y + 1 == i || player1y + 2 == i))
				{
					cout << "\xDB";
				}
				else if (player2x == j && (player2y == i || player2y + 1 == i || player2y + 2 == i))
				{
					cout << "\xDB";
				}
				else
				{
					cout << " ";
				}
			}
			cout << endl;
		}
		//down wall
		for (int i = 0; i < width + 2; i++)
		{
			cout << "\xB2";
		}
		cout << endl;
		cout << "Player 1 : " << score1 << endl;
		cout << "Player 2 : " << score2 << endl;
	}
	void Input()
	{
		ball->Move();

		if (_kbhit())
		{
			char current = _getch();
			if (current == up1&&player1->getY()>0) 
			{
				player1->MoveUP();
			}
			if (current == down1 && player1->getY() + 4 < height)
			{
				player1->MoveDown();
			}
			if (current == up2 && player2->getY() > 0)
			{
				player2->MoveUP();
			}
			if (current == down2 && player2->getY() + 4 < height)
			{
				player2->MoveDown();
			}
			if (ball->getDirection() == STOP)
			{
				ball->randomDirection();
				if (current == 'q')
				{
					quit = true;

				}
			}
		}
	}
	void Logic()
	{
		//ball position
		int ballx = ball->GetX();
		int bally = ball->GetY();
		//players positions
		int player1x = player1->getX();
		int player1y = player1->getY();
		int player2x = player2->getX();
		int player2y = player2->getY();

		//on left padle hit
		for (int i = 0; i < 4; i++)
		{
			if (ballx == player1x + 1)
				if (bally == player1y + i)
					ball->ChangeDirection((Dir)((rand()%3)+4));
			
		}
		//on right padle hit
		for (int i = 0; i < 4; i++)
		{
			if (ballx == player2x - 1)
				if (bally == player2y + i)
					ball->ChangeDirection((Dir)((rand() % 3) + 1));

		}
		//ball, on  hit the bottomwall
		if (bally == height - 1)
		{
			//if it are gone downright bounce upright else upleft
			ball->ChangeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);
		}
		//ball, on hit upwall
		 if (bally == 0)
		{
			ball->ChangeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
		}
		 //Goal
		 if (ballx == width - 1)
		 {
			 scoreUp(player1);
		 }
		 if (ballx == 0)
		 {
			 scoreUp(player2);
		 }
	}
	void Run()
	{
		while (!quit)
		{
			Draw();
			Input();
			Logic();
			Sleep(20);
		}
	}
};
int main()
{
	GameManager *game = new GameManager(25, 10);
	game->Run();

	return 0;
}


