#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "Snake.h"
#include "Collectable.h"
#include "Wall.h"

#include <sstream>
#include <string>

class Gameplay
{
    public:
        int sSize1;
        int sSize2;
        bool glueTaken = false;
        bool gameOver;
        std::string winner;
        Collectable apple1;
        Collectable apple2;
        Collectable apple3;
        Collectable glue;
        int itemToStore[2] = {0,0};
        int snakeScore[2]={0,0};
        int rgbGreen[3]={0,255,0};
        int rgbYellow[3]={255,255,0};
        int pos1[2]={170,0};
        int pos2[2]={250,0};
        int pos3[2]={550,0};
        int pos4[2]={630,0};


        Gameplay();
        int collideWithApple(Snake *player, int sSize, int index, Collectable *apple);
        void collideWithGlue(Snake *player, Collectable *glue, int indexPlayer);
        void displayBag(sf::RenderWindow *mWindow, Snake player, int txtX, int txtY);
        void collideWithWall(Snake *player, std::string playerNum);
        void collideWithItself(Snake *player, std::string playerNum);
        void collideWithSnake(Snake *player1, Snake *player2);
        void collision(Snake *player1, Snake *player2, Collectable *apple);
        std::string castToString(int a);
        void displayText(sf::RenderWindow *mWindow, int rgb[3], int pos[2], std::string txt, int txtSize);
        void getWinner(sf::RenderWindow *window);
        void play(sf::RenderWindow *gameplayWindow);
};

#endif // GAMEPLAY_H
