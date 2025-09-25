#include "Game.h"

//load image data from passed .txt file into passed array
void Game::Loadimage(string filename, BoardData image[50][50]) {
    int rows, columns;
    ifstream input(filename);
    if (!input)
        return;
    input >> rows >> columns;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
            input >> image[i][j].symbol >> image[i][j].color >> image[i][j].bgcolor;
    }
    input.close();
}
//Display images that have been loaded. Hardcode size of 25 x 50
void Game::Displayimage(int x, int y, BoardData image[50][50]) {
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            gotoxy(j + x, i + y);
            setForeGroundAndBackGroundColor(image[i][j].color, image[i][j].bgcolor);
            cout << char(image[i][j].symbol);
        }
    }
}
//creates start screen that prevents demonstration from starting before user input. Displays story info and art
void Game::startScreen() {
    //load and display start image
    Loadimage("files/start.txt", images[0]);
    Displayimage(0, 0, images[0]);
    setcolor(15); //make text white
    //write text to the right of the start image
    gotoxy(51, 10);
    cout << "This is the story of the automated exploration ship Omegan,";
    gotoxy(51, 11);
    cout << "attempting to chart a path through the Astera Nebula.";
    gotoxy(51, 12);
    cout << "To begin the demonstration, type any character and press enter.";
    //take meaningless user input to progress
    char x;
    cin >> x;
    //clear screen
    system("cls");

}
//create starting game state
void Game::setup() {
    //load and display maze
    Loadimage("files/maze.txt", maze);
    Displayimage(0, 0, maze);
    //set starting position
    xpos = 0;
    ypos = 4;
}
//display end state. Place in infinite loop to make screen static
void Game::endScreen() {
    //Load and display ending image
    Loadimage("files/end.txt", images[1]);
    Displayimage(0, 0, images[1]);
    setcolor(15); //make text white
    //put text to right of image
    gotoxy(51, 10);
    //display move counter, since path is always the same will always display same result
    cout << "Moves: " << moves;
    gotoxy(51, 11);
    cout << "After Omegan made it through the Nebula,";
    gotoxy(51, 12);
    cout << "it went on to find the habitable exoplanet Redava.";
    gotoxy(51, 13);
    cout << "Omegan's path through the Nebula was refined";
    gotoxy(51, 14);
    cout << "and used to program the enusing colony ships.";
    M.Play(L"files/victory.wav", NULL, SND_LOOP); //play victory music

}


//Place X symbol repersenting ship at current location
void Game::DisplayShip() {
    gotoxy(xpos, ypos);
    cout << "X";
}
//Hide ship to create illusion of movement
void Game::HideShip() {
    gotoxy(xpos, ypos);
    cout << " ";
}
//See if space ship wants to move from is its last position at the top of the stack
bool Game::NotFrom(int x, int y) { //return true if the space the X is considering isn't where it just came from
    point p = S.peek(); //return top of stack without removing it
    if (x == p.x && y == p.y) {
        return false;
    }
    return true;
}
//"AI" of the ship
void Game::MoveShip() {
    //logic has been reordered so the ship doesn't take the longest possible path
    //right
    if ((maze[ypos][xpos + 1].symbol == 32) && (NotFrom(xpos + 1, ypos))) { //for some reason x and y are reversed inside BoardData
        S.push(xpos, ypos); //add current location to stack
        xpos++; //move right
    }
    //down
    else if ((maze[ypos + 1][xpos].symbol == 32) && (NotFrom(xpos, ypos + 1))) {
        S.push(xpos, ypos); //add current location to stack
        ypos++; //move down
    }
    //left
    else if ((maze[ypos][xpos - 1].symbol == 32) && (NotFrom(xpos - 1, ypos))) {
        S.push(xpos, ypos); //add current location to stack
        xpos--; //move right
    }
    //up
    else if ((maze[ypos - 1][xpos].symbol == 32) && (NotFrom(xpos, ypos - 1))) {
        S.push(xpos, ypos); //add current location to stack
        ypos--; //move up
    }
    else { //back track
        maze[ypos][xpos].symbol = 178; //mark the places as already gone
        //go to previous location, pop from stack
        point p;
        p = S.pop();
        xpos = p.x;
        ypos = p.y;
    }
    moves++; //iterate move counter
}
