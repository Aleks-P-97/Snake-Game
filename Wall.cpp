#include "Wall.h"

Wall::Wall()
{

}


void Wall::createWalls(int vericalX, int vericalY, int horizontalX, int horizontalY)
{
    //size
    verticalWall.setSize({10,600});
    horizontalWall.setSize({800,10});

    //set position
    verticalWall.setPosition(vericalX,vericalY);
    horizontalWall.setPosition(horizontalX,horizontalY);

    //colour
    verticalWall.setFillColor(sf::Color::White);
    horizontalWall.setFillColor(sf::Color::White);
}


void Wall::drawWalls(sf::RenderWindow *mWindow)
{
    mWindow->draw(verticalWall);
    mWindow->draw(horizontalWall);
}
