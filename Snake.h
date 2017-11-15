#ifndef SNAKE_H
#define SNAKE_H
#include "Collectable.h"
#include <SFML/Graphics.hpp>
#include <list>

class Snake
{
    public:
        sf::RectangleShape segment;
        std::list<sf::RectangleShape> segmentList;
        std::list<sf::CircleShape> bag;
        Collectable glue;
        bool isAlive;
        bool pl1GlueDropped;
        bool pl2GlueDropped;
        int snakeX;
        int snakeY;
        int snakeSize;
        int snakesCoordinates[4];

        Snake(int x, int y);
        void createSnake(int r, int g, int b);
        void appendToBag(int itemToStore);
        void breakMovement(int player);
        void dropGlue(int player);
        void grow(int sSize, int player);
        void getMovement(int player);
        void drawSnake(sf::RenderWindow *mWindow);
};

#endif // SNAKE_H
