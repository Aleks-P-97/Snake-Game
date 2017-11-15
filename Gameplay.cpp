/*
  This is where the ... is made.
*/

#include "Gameplay.h"
#include "Snake.h"
#include "Collectable.h"
#include "Wall.h"

#include <string>
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>

using namespace std;

Gameplay::Gameplay()
{
    sSize1 = 10;
    sSize2 = 10;
    gameOver = false;
}

void Gameplay::collideWithItself(Snake *player, std::string playerNum)
{
    /*
     * This variable will be used to check collision
     * after the first seg in the list because the first seg
     * is the same as player.segment. So this means it will
     * always intersect.
     */
    int flag = 0;

    for (sf::RectangleShape seg : player->segmentList)
    {

        if (player->segment.getGlobalBounds().intersects(seg.getGlobalBounds()) && flag > 2)
        {
            //cout << "player " << playerNum <<" has won!!!!!!" <<endl;
            winner = "The winner is " + playerNum + "!";
            gameOver = true;
        }
        flag++;
    }
}


void Gameplay::collideWithSnake(Snake *player1, Snake *player2)
{

    //Player 1 bites player 2
    for (sf::RectangleShape seg2 : player2->segmentList)
    {
        if(player1->segment.getGlobalBounds().intersects(seg2.getGlobalBounds()))
        {
            cout << "player 2 wins" <<endl;
            winner = "The winner is player 2(Yellow)!!";
            gameOver = true;
        }
    }

    //Player 2 bites player 1
    for (sf::RectangleShape seg1 : player1->segmentList)
    {
         if(player2->segment.getGlobalBounds().intersects(seg1.getGlobalBounds()))
        {
            cout << "player 1 wins" <<endl;
            winner = "The winner is player 1(Green)!!";
            gameOver = true;
        }
    }

    //The two players' heads collide
    if (player1->segment.getGlobalBounds().intersects(player2->segment.getGlobalBounds()))
    {
        if(snakeScore[0] > snakeScore[1])
        {
            cout<< "player 1 wins" <<endl;
            winner = "The winner is player 1(Green)!";
            gameOver = true;
        }else if(snakeScore[0] > snakeScore[1])
        {
            cout<< "player 2 wins" <<endl;
            winner = "The winner is player 2(Yellow)!";
            gameOver = true;
        }else if(snakeScore[0] == snakeScore[1])
        {
            cout<< "Its a draw" <<endl;
            winner = "Its a draw!";
            gameOver = true;
        }
    }
}



int Gameplay::collideWithApple(Snake *player, int sSize, int index, Collectable *apple)
{
    bool eaten = false;

    if (player->segment.getGlobalBounds().intersects(apple->appleBlock.getGlobalBounds()))
    {
        snakeScore[index] += 1;
        sSize++;
        cout<< "APPLE EATEN!" << endl;
        eaten = true;

        if(eaten == true)
        {
            apple->randomCoordinates();
            apple->createApple(255,0,0);
            eaten = false;
        }
    }

    return sSize;
}


void Gameplay::collideWithGlue(Snake *player, Collectable *glue, int indexPlayer)
{
    if (player->segment.getGlobalBounds().intersects(glue->triangle.getGlobalBounds()))
    {

        if(player->bag.size() <4)
        {
            //cout << "I have a glue!!" << player->bag.size()<< endl;
            itemToStore[indexPlayer] = 1;
            glueTaken = true;
            glue->randomCoordinates();
            glue->createGlue(0,0,255);
        }
    }
}


void Gameplay::displayBag(sf::RenderWindow *mWindow, Snake player, int txtX, int txtY)
{
    int glueX;
    int glueY = 15;

    int rgb[3]={0,0,255};
    int pos[2]={txtX,txtY};

    glueX = txtX+60;

    displayText(mWindow,rgb, pos, "Bag: ", 30);

    for (sf::CircleShape glueInBag : player.bag)
    {
        glueInBag.setPointCount(3);
        glueInBag.setRadius(10);
        glueInBag.setFillColor(sf::Color(0,0,255));
        glueInBag.setPosition(glueX,glueY);
        mWindow->draw(glueInBag);
        glueX+=21;
    }
}


void Gameplay::collideWithWall(Snake *player, std::string playerNum)
{
    if (player->snakeX <= 10 || player->snakeX >= 790)
    {
        cout << " Hit a vertical wall! "  << endl;
        winner = "The winner is " + playerNum + "!";
        gameOver = true;
    }

    if(player->snakeY <= 40 || player->snakeY >= 590)
    {
        cout << "Hit a horizontal wall" << endl;
        winner = "The winner is " + playerNum + "!";
        gameOver = true;
    }
}


//This method calls all the methods that deal with collision
void Gameplay::collision(Snake *player1, Snake *player2, Collectable *apple)
{

    //The collideWithApple function returns the size & the score of the snake so that they can be updated.
    sSize1 = collideWithApple(player1, sSize1, 0, apple);
    sSize2 = collideWithApple(player2, sSize2, 1, apple);

    collideWithGlue(player1, &glue, 0);
    collideWithGlue(player2, &glue, 1);

    collideWithWall(player1, "2");
    collideWithWall(player2, "1");

    collideWithItself(player1, "2");
    collideWithItself(player2, "1");

    collideWithSnake(player1, player2);
}


string Gameplay::castToString(int a)
{
    stringstream ss;
    ss << a;
    string str = ss.str();

    return str;
}


void Gameplay::displayText(sf::RenderWindow *mWindow, int rgb[3], int pos[2], std::string txt, int txtSize)
{

    //Add font
    sf::Font font;

    if (!font.loadFromFile("BOD_I.TTF"))
    {
        std::cout << "Can't find the font file!" << std::endl;
    }

    sf::Text text(txt, font, txtSize);


    text.setPosition({pos[0],pos[1]});

    text.setColor(sf::Color(rgb[0],rgb[1],rgb[2]));

    mWindow->draw(text);
}


void Gameplay::getWinner(sf::RenderWindow *window)
{
    int rgb[3]={172,0,255};
    int pos[2]={150,300};

    displayText(window, rgb, pos, winner, 50);

    sf::sleep(sf::milliseconds(2000));
    cout << "I'm in" << endl;
}


//The loop that runs the gameplay
void Gameplay::play(sf::RenderWindow *gameplayWindow)
{
    sf::Clock clock;
    sf::Time t1 = clock.getElapsedTime();
    sf::Int32 msec = t1.asMilliseconds();
    gameOver = false;

    Wall wall1;
    Wall wall2;

    Snake player1(600,300);
    Snake player2(200,300);

    //Create walls
    wall1.createWalls(0,0, 0,590);//Takes in Left wall & Bottom wall coordinates
    wall2.createWalls(790,0, 0,40);//Takes in Right wall & Top wall coordinates

    apple1.randomCoordinates();
    apple1.createApple(255,0,0);

    apple2.randomCoordinates();
    apple2.createApple(255,0,0);

    apple3.randomCoordinates();
    apple3.createApple(255,0,0);

    glue.randomCoordinates();
    glue.createGlue(0,0,255);

    gameplayWindow->setKeyRepeatEnabled(false);

     while (gameplayWindow->isOpen())
    {
        sf::Event event;
        while (gameplayWindow->pollEvent(event))
        {
          switch(event.type)
          {
            case sf::Event::Closed:
              gameplayWindow->close();
            break;
            default:
              break;
          }
        }

        //Refreshing the window
        gameplayWindow->clear();

        //Game Over
        if(gameOver == true)
        {
            getWinner(gameplayWindow);
            gameplayWindow->display();
            sf::sleep(sf::milliseconds(2000));
            break;

        }

        /*Gameplay*/

        //Drawing walls
        wall1.drawWalls(gameplayWindow);
        wall2.drawWalls(gameplayWindow);


        //Creates the snakes and sets/re-sets the position of the head
        player1.createSnake(0, 255, 0);
        player2.createSnake(255, 255, 0);


        //Keeps the size of the snake growing only by 1 segment
        player1.grow(sSize1,1);
        player2.grow(sSize2,2);


        //Checks if the snake picked up a glue
        if(glueTaken == true)
        {
            player1.appendToBag(itemToStore[0]);
            player2.appendToBag(itemToStore[1]);

            itemToStore[0] = 0;
            itemToStore[1] = 0;
            glueTaken = false;
        }

        //Movement
        player1.getMovement(1);
        player2.getMovement(2);

        player1.breakMovement(1);
        player2.breakMovement(2);


        //Set coordinates so that the snakes can move continuously
        player1.snakeX += player1.snakesCoordinates[0];// moves the snake1 left or right
        player1.snakeY += player1.snakesCoordinates[1];// moves the snake1 up or down
        player2.snakeX += player2.snakesCoordinates[2];// moves the snake2 left or right
        player2.snakeY += player2.snakesCoordinates[3];// moves the snake2 up or down


        //This block introduces delay in the snake's movement.
        while (clock.getElapsedTime().asMilliseconds()<100);
        clock.restart();


        //Check collision
        collision(&player1, &player2, &apple1);
        collision(&player1, &player2, &apple2);
        collision(&player1, &player2, &apple3);
        collision(&player1, &player2, &glue);


        //Draws the Collectables
        gameplayWindow->draw(apple1.appleBlock);
        gameplayWindow->draw(apple2.appleBlock);
        gameplayWindow->draw(apple3.appleBlock);
        gameplayWindow->draw(glue.triangle);

        //if(player1.isAlive == true)
        //{
            player1.drawSnake(gameplayWindow);
        //}


       // if(player2.isAlive == true)
       // {
            player2.drawSnake(gameplayWindow);
        //}

        //To show how many glues each player has
        displayBag(gameplayWindow, player1, 15,0);
        displayBag(gameplayWindow, player2, 395,0);

        //Convert the score to a string
        std::string scoreTxt1 = castToString(snakeScore[0]);
        std::string scoreTxt2 = castToString(snakeScore[1]);

        //Set up score for player1
        displayText(gameplayWindow, rgbGreen, pos1, "Score:", 30);
        displayText(gameplayWindow, rgbGreen, pos2, scoreTxt1, 30); //The actual score of player 1


        //Set up score for player2
        displayText(gameplayWindow, rgbYellow, pos3, "Score:", 30);
        displayText(gameplayWindow, rgbYellow, pos4, scoreTxt2, 30); //The actual score of player 2


        //Get the window to display its contents
        gameplayWindow->display();

        //Controls the pace of the snakes
        gameplayWindow->setFramerateLimit(60);
    }
}
