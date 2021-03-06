// snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <string>
#include <iomanip>
#include <ctime>
#include <Windows.h>


using namespace std;

//plublic variables
const int maxX = 150;
const int maxY = 35;
//storing info for the whole map
int playfield[maxX][maxY];

char ch = 'a';
int oldDirect = 4;
int score;

int foodX;
int foodY;



class Score {
private:
	int currentScore;
public:
	Score() {
		currentScore = 0;
	}
	void addScore() {
		currentScore++;
	}
	int seeScore() {
		return currentScore;
	}
};


int direction(char in){
	if (in == 'w' and oldDirect !=3) {
		oldDirect = 1;
		return 1;//up
	}
	if (in == 'a' and oldDirect !=4) {
		oldDirect = 2;
		return 2;
	}//left
	if (in == 's' and oldDirect !=1 ) {
		oldDirect = 3;
		return 3;
	}//down
	if (in == 'd' and oldDirect !=2) {
		oldDirect = 4;
		return 4;
	}//right
	else return oldDirect;
}

void addFood() {
	foodX = rand() % (maxX-1) + 1;
	foodY = rand() % (maxY-1) + 1;
	while (playfield[foodX][foodY] != 0 or playfield[foodX][foodY + 1] !=0 or playfield[foodX+1][foodY] != 0 or playfield[foodX+1][foodY + 1] != 0) {
		foodX = rand() % maxX + 1;
		foodY = rand() % maxY + 1;
	}
	playfield[foodX][foodY] = -1;
	playfield[foodX][foodY+1] = -1;
	playfield[foodX+1][foodY] = -1;
	playfield[foodX+1][foodY+1] = -1;

	
}

void clearFood() {
	for (int a = 0; a <= maxY; a++) {
		for (int b = 0; b <= maxX; b++) {
			if (playfield[b][a] == -1) {
				playfield[b][a] = 0;
			}
		}
	}
}


void updateSnake(int directi, int & x, int & y, int & score, int & snakeLength, int & game ) {
	
	if (directi == 1) { //up
		y--;
	}
	//left
	if (directi == 2) x=x-2;
	//down
	if (directi == 3) y++;
	//right
	if (directi == 4) x=x+2;

	//check for wall and teleport to the opposite side
	if (x >= maxX) x = 1 + (x - maxX);
	if (x <= 0) x = (maxX - 1) + x;
	if (y >= maxY) y = 1 + (y - maxY);
	if (y <= 0) y = (maxY - 1) + y;


	//check for self-eat
	if (playfield[x][y] > 0) {
		game = 0;
	}



	//check for food coalition
	if (playfield[x][y] == -1) {
		playfield[x][y] = snakeLength;
		for (int a = 0; a <= maxY; a++) {
			for (int b = 0; b <= maxX; b++) {
				if (playfield[b][a] > 0) {
					playfield[b][a]--;
				}
			}
		}
		score++;
		snakeLength += 5;
		clearFood();
		addFood();


	}
	else {
		//put the snake to a new position 
		playfield[x][y] = snakeLength;
		for (int a = 0; a <= maxY; a++) {
			for (int b = 0; b <= maxX; b++) {
				if (playfield[b][a] > 0) {
					playfield[b][a]--;
				}
			}
		}
	}

	


	

}

//obsolete
void updatePlayfieldSnake(int x, int y, int snakeLength) {
	
	playfield[x][y] = snakeLength;
	for (int a = 0; a <= maxY; a++) {
		for (int b = 0; b <= maxX; b++) {
			if (playfield[b][a] > 0 ) {
				
					playfield[b][a]--;
				
				
			}
		}
	}
}


//ui for the game
void drawbox(int snake0, int snake1) //https://stackoverflow.com/questions/4789346/how-can-i-make-cout-faster
{
	
	
	string str = "";
	str.reserve(maxX * maxY);

	for (int a = 0; a <= maxY; a++) {
		for (int b = 0; b <= maxX; b++) {
			if ((a == 0 and b == 0) or (a == maxY and b == maxX) or (a == 0 and b == maxX) or (a == maxY and b == 0)) {
				str += '+';
			}
			else if (a == 0 or a == maxY) {
				str += '-';
			}
			else if (b == 0 or b == maxX) str += '|';
			else if (playfield[b][a] >= 1) {
				str += '*';
			}
			else if (playfield[b][a] <= -1) {
				str += '+';
			}
			else {
				str += ' ';
			}

		}
		str += '\n';
	}
	cout << str ;
	

	
}

int main()
{
	int game = 1; //lose as game =0
	int snakeLength = 8;
	int score = 0;
	char chs = ' ';


	srand(time(NULL));
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	int snake[2];
	
	int direct = 4;
	

	//initial position
	snake[0] = 20;//x
	snake[1] = 5;
	//storing info for the whole map
	
	//initial empty playfield
	for (int a = 0; a <= maxY; a++) {
		for (int b = 0; b <= maxX; b++) {
			playfield[b][a] = 0;
			
		}
	}

	addFood();
	while (game) {
		system("CLS");

		//updatePlayfieldSnake(snake[0], snake[1]);
		drawbox(snake[0], snake[1]);

		//drawbox(snake[0], snake[1]);
		/*
		for (int a = 0; a <= maxY; a++) {
			for (int b = 0; b <= maxX; b++) {
				if ((a == 0 and b == 0) or (a == maxY and b == maxX) or (a == 0 and b == maxX) or (a == 35 and b == 0)) {
					cout << "+";
				}
				else if (a == 0 or a == maxY) {
					cout << "-";
				}
				else if (b == 0 or b == maxX) cout << "|";
				else if (snake[0] == b and snake[1] == a) {
					cout << "*";
				}
				else cout << " ";

			}
			cout << endl;
		}*/
		//cout<<"aaaaaaaaaaaa"<<_kbhit()<<" "<< direction(ch) <<endl;
		if (_kbhit()) {
			//cout << "pressed" << " ";
			chs = _getch();
			//cout << snake[0]<<" "<<snake[1]<<" ";
			//Sleep(500);
			//updateSnake(direct, snake[0], snake[1]);
		}
		if (_kbhit()) {
			//get rid of the space
			char chsa = _getch();
			
		}
		direct = direction(chs);
		updateSnake(direct, snake[0], snake[1], score, snakeLength, game);
		cout << "Score: "<<score;
		//Sleep(500);
		//addFood();
		//cout << score<< snakeLength;
		
	}
	system("CLS");
	cout << "You lost!";
	cin.ignore();
	//Sleep(50);
}

