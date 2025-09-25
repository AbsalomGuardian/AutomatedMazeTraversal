#include "Stack.h"
#include "TextDraw.h"
#include <fstream>
#include <iostream>
#include "MySound.h"
#include "Coordinates.h"
using namespace std;

//class that controls the entire game
class Game : public Coordinates {
public:
	//member variables
	//maze stores game board. images stores the start and end screens
	BoardData maze[50][50];
	BoardData images[2][50][50];
	int xpos, ypos;
	int moves = 0;
	//member objects
	MySound M;
	Stack S;
	//Coordinates C;
	//management functions
	void Loadimage(string filename, BoardData image[50][50]); //not camel case because LoadImage is reserved
	void Displayimage(int x, int y, BoardData image[50][50]);
	void startScreen();
	void setup();
	void endScreen();
	//game functions
	void DisplayShip();
	void HideShip();
	bool NotFrom(int x, int y);
	void MoveShip();



};