#include "Snake.h"
#include "Collectable.h"
#include <iostream>
#include <list>

using namespace std;

Snake::Snake(int x, int y)
{
    snakeX = x;
    snakeY = y;
    snakeSize = 10;
    isAlive = true;
    pl1GlueDropped = false;
    pl2GlueDropped = false;

    //Default coordinates for player 1
    snakesCoordinates[0] = -10;
    snakesCoordinates[1] = 0;

    //Default coordinates for player 2
    snakesCoordinates[2] = 10;
    snakesCoordinates[3] = 0;
}


//Makes the snake grow when it collides with an apple.
void Snake::createSnake(int r, int g, int b)
{
    segment.setSize({15,15});
    segment.setPosition(snakeX, snakeY);
    segment.setFillColor(sf::Color(r, g, b));
}


//Keeps the snake size while it moves
void Snake::grow(int sSize, int player)
{
    if(player == 1 && pl1GlueDropped == false)
    {
        segmentList.push_front(segment);
    }

    if(player == 2 && pl2GlueDropped == false)
    {
        segmentList.push_front(segment);
    }

    if(segmentList.size() > sSize)
    {
        segmentList.pop_back();
        snakeSize = sSize;
    }
}

void Snake::appendToBag(int itemToStore)
{
    if(itemToStore == 1)
    {
        bag.push_front(glue.triangle);
    }
}

void Snake::dropGlue(int player)
{
    bag.pop_back();
    if(player == 1)
    {
        pl1GlueDropped = true;
    }else if(player == 2)
    {
        pl2GlueDropped = true;
    }
}


void Snake::drawSnake(sf::RenderWindow *mWindow)
{
    for (sf::RectangleShape seg1 : segmentList)
    {
        mWindow->draw(seg1);
    }
}


void Snake::getMovement(int player)
{
    //Controls for player 1
    if(player == 1)
    {
        if((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && snakesCoordinates[1] != 10)
        {
            snakesCoordinates[0] = 0;   //X coordinates of the snake
            snakesCoordinates[1] = -10; //Y coordinates of the snake
            pl1GlueDropped = false;
        } else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && snakesCoordinates[1] != -10)
        {
            snakesCoordinates[0] = 0;   //X coordinates of the snake
            snakesCoordinates[1] = 10;  //Y coordinates of the snake
            pl1GlueDropped = false;
        }else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && snakesCoordinates[0] != 10)
        {
            snakesCoordinates[0] = -10; //X coordinates of the snake
            snakesCoordinates[1] = 0;   //Y coordinates of the snake
            pl1GlueDropped = false;
        }else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && snakesCoordinates[0] != -10)
        {
            snakesCoordinates[0] = 10;  //X coordinates of the snake
            snakesCoordinates[1] = 0;   //Y coordinates of the snake
            pl1GlueDropped = false;
        }
    }


    //Controls for player 2
    if(player = 2)
    {
        if((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && snakesCoordinates[3] != 10)
        {
            snakesCoordinates[2] = 0;   //X coordinates of the snake
            snakesCoordinates[3] = -10; //Y coordinates of the snake
            pl2GlueDropped = false;
        } else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && snakesCoordinates[3] != -10)
        {
            snakesCoordinates[2] = 0;   //X coordinates of the snake
            snakesCoordinates[3] = 10;  //Y coordinates of the snake
            pl2GlueDropped = false;
        }else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && snakesCoordinates[2] != 10)
        {
            snakesCoordinates[2] = -10; //X coordinates of the snake
            snakesCoordinates[3] = 0;   //Y coordinates of the snake
            pl2GlueDropped = false;
        }else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && snakesCoordinates[2] != -10)
        {
            snakesCoordinates[2] = 10;  //X coordinates of the snake
            snakesCoordinates[3] = 0;   //Y coordinates of the snake
            pl2GlueDropped = false;
        }
    }

}


//If there's a glue present in the bag a break can be applied by pressing shift.
void Snake::breakMovement(int player)
{

    if(player == 1 && bag.size() % 5)
    {
         //Break for player 1
        if((sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)))
        {
            snakesCoordinates[0] = 0;  //X coordinates of the snake
            snakesCoordinates[1] = 0;  //Y coordinates of the snake
            dropGlue(player);
        }
    }


    if(player == 2 && bag.size() % 5)
    {
        //Break for player 2
        if((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)))
        {
            snakesCoordinates[2] = 0;  //X coordinates of the snake
            snakesCoordinates[3] = 0;   //Y coordinates of the snake
            dropGlue(player);
        }
    }
}

