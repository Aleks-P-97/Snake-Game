#ifndef COLLECTABLE_H
#define COLLECTABLE_H

#include <SFML/Graphics.hpp>

class Collectable //make this a super class of apple & glue
{
    public:
        int itemX;
        int itemY;
        sf::RectangleShape appleBlock;
        sf::CircleShape triangle;

        Collectable();
        void randomCoordinates();
        void createApple(int r, int g, int b);
        void createGlue(int r, int g, int b);

};

#endif // COLLECTABLE_H
