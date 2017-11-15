#include "Collectable.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <random>
#include <SFML/Graphics.hpp>

using namespace std;

Collectable::Collectable()
{

}


void Collectable::createApple(int r, int g, int b)//this method will not draw
{
    appleBlock.setSize(sf::Vector2f(10, 10));
    appleBlock.setPosition(itemX,itemY);
    appleBlock.setFillColor(sf::Color(r,g,b));
}


void Collectable::createGlue(int r, int g, int b)//this method will not draw
{
    triangle.setRadius(15);
    triangle.setPointCount(3);
    triangle.setPosition(itemX,itemY);
    triangle.setFillColor(sf::Color(r,g,b));
}


//Generates random coordinates for the apple
void Collectable::randomCoordinates()
{
    itemX = (rand()% 750)+10;
    itemY = (rand()% 500)+50;
}


    //If I have time to make the item stay visible only for a certain time
    //so that if it isn't eaten in that time it would disappear and another item will appear.



