#ifndef WALL_H
#define WALL_H

#include <SFML/Graphics.hpp>

class Wall
{
    public:
        sf::RectangleShape horizontalWall;
        sf::RectangleShape verticalWall;

        Wall();
        void createWalls(int vericalX, int vericalY, int horizontalX, int horizontalY);
        void drawWalls(sf::RenderWindow *mWindow);
};

#endif // WALL_H
