#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
using namespace std;

bool gameOver;
const int widthofwall = 20;
const int heightofwall = 10;
int xAxis, yAxis , foodX, foodY, score;
int tailX[100], tailY[100];
int nTail, highestScore;

enum Directions
{
    stop = 0, moveLeft, moveRight, moveUp, moveDown 
};
Directions dir;

void LoadHighestScore() {
    ifstream file("highest_score.txt");
    if (file.is_open()) {
        file >> highestScore;
        file.close();
    }
}

void SaveHighestScore() {
    ofstream file("highest_score.txt");
    if (file.is_open()) {
        file << highestScore;
        file.close();
    }
}

void Boot()
{
    LoadHighestScore(); 
    gameOver = false;
    dir = stop;
    xAxis = widthofwall / 2;
    yAxis = heightofwall / 2;
    foodX = rand() % widthofwall;
    foodY = rand() % heightofwall;
    score = 0;
}

void Design()
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),{0,0});
    for (int i = 0; i <= widthofwall; i++)
    {   
        cout << "# ";
    }
    cout <<endl;
    for (int i = 0; i <= heightofwall; i++)
    {
        for (int j = 0; j <= widthofwall; j++)
        {
            if (j == 0 || j == widthofwall){
                cout << "#";
            }
            else{
                cout <<" ";
            }
            if (i == yAxis && j == xAxis){
                cout << "0";
            } 
            else if (j == foodX && i == foodY)
            {
                cout << "*";
            }
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
        }
        cout << endl;
    }
    for (int i = 0; i <= widthofwall; i++)
    {   
        cout << "# ";
    }
    cout << endl;
    cout << "Current Score: " << score << endl;
    cout << "Highest Score: " << highestScore << endl;
}
void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = moveLeft;
            break;
        case 'd':
            dir = moveRight;
            break;
        case 'w':
            dir = moveUp;
            break;
        case 's':
            dir = moveDown;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }

}
void MainLogic()
{
    for (int i = nTail; i > 0; i--)
    {
        tailX[i] = tailX[i-1];
        tailY[i] = tailY[i-1];
    }
        tailX[0] = xAxis;
        tailY[0] = yAxis;

    switch (dir)
    {
    case moveLeft:
        xAxis--;
        break;
    case moveRight:
        xAxis++;
        break;
    case moveUp:
        yAxis--;
        break;
    case moveDown:
        yAxis++;
        break;
    }

    if ((xAxis > widthofwall || xAxis < 0) || (yAxis > heightofwall || yAxis < 0))
    {
        cout << "Game Over!" << endl;
        gameOver = true;
    }

    for (int i = 0; i < nTail; i++)
    {
        if (tailX[i] == xAxis && tailY[i] == yAxis)
        {
            cout << "Game Over!" << endl;
            gameOver = true;
        }
    }

    if (xAxis == foodX && yAxis == foodY) {
        score = score + 10;
        if (score > highestScore) {
            highestScore = score;
            SaveHighestScore();
        }
        nTail++;
        foodX = rand() % widthofwall;
        foodY = rand() % heightofwall;
    }
}

int main()
{   
    Boot();
    while (!gameOver)
    {   system("Color 0A");
        Design();
        Input();
        MainLogic();
        Sleep(0);
    }
    cout << foodX << " " << foodY;
    system("pause");
    return 0;
}