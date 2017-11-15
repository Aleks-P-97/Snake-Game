/*
  Snake ICA start project using SFML
    SFML documentation: http://www.sfml-dev.org/documentation/2.4.2/classes.php
  Windows build
    To build on Windows you need to have the correct version of CodeBlocks
      Download from here: http://www.codeblocks.org/downloads/26
      Must be the download titled "codeblocks-16.01mingw-setup.exe"
*/

#include <iostream>
#include "Gameplay.h"
#include "Collectable.h"

// SFML header file for graphics, there are also ones for Audio, Window, System and Network
#include <SFML/Graphics.hpp>

int main()
{
    // All SFML types and functions are contained in the sf namespace

    // Create an instance of the SFML RenderWindow type which represents the display
    // and initialise its size and title text
    sf::RenderWindow mainWindow(sf::VideoMode(800, 600), "C++ Snake ICA : U0018197");

    //Creating a font
    sf::Font font;

    if (!font.loadFromFile("BOD_I.TTF"))
    {
        std::cout << "Can't find the font file!" << std::endl;
    }


    //Start text
    sf::Text startText("Press space to start the game..", font, 30);
    startText.setPosition({230,530});
    startText.setColor(sf::Color::Black);


    //Background img
    sf::Texture texture;
    if (!texture.loadFromFile("snakeIMG.png"))
    {
        std::cout << "The image can't be found!" << std::endl;
    }


    //Background Sprite
    sf::Sprite background;
    background.setTexture(texture);


    // We can still output to the console window
    std::cout << "Starting" << std::endl;

    Gameplay gameplay;
    // Main loop that continues until we call Close()
    while (mainWindow.isOpen())
    {

        // Handle any pending SFML events
        // These cover keyboard, mouse,joystick etc.
        sf::Event event;
        while (mainWindow.pollEvent(event))
        {
          switch(event.type)
          {
            case sf::Event::Closed:
                mainWindow.close();
            break;
            default:
              break;
          }
        }

        // We must clear the window each time round the loop
        mainWindow.clear();

        mainWindow.draw(background);
        mainWindow.draw(startText);

        if((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)))
        {
            gameplay.play(&mainWindow);
            std::cout << "Closing main menu..";
        }

        // Get the window to display its contents
        mainWindow.display();
    }


    std::cout << "Finished" << std::endl;
    return 0;
}

