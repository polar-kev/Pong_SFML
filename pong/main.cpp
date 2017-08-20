
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//
// Sounds from: http://www.bigsoundbank.com/

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
//#include "stdafx.h"
#include "Bat.hpp"
#include "Ball.hpp"
#include <sstream>
#include <cstdlib>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"

int main(int, char const**)
{
    const float windowWidth = 1024;
    const float windowHeight = 768;
    const int FRAMES_PER_SECOND = 25;
    const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;
    int sleepTime = 0;
    
    std::string stringPlayer1Score, stringPlayer2Score;
    
    sf::Clock clock;
    float time1 = clock.getElapsedTime().asMilliseconds();
    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Pong");
    window.setFramerateLimit(25);

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    //create game objects
    Bat bat (windowWidth-20, windowHeight/2);
    Bat bat2 (10, windowHeight/2);
    Ball ball(windowWidth/2,windowHeight/2);
    
    int player1Score = 0;
    int player2Score = 0;
    
    
    // Create text and a font
    sf::Text hudLeft;
    sf::Text hudRight;
    sf::Font font;
    
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    
    hudLeft.setPosition(100, 0);
    hudLeft.setFont(font);
    hudLeft.setCharacterSize(40);
    hudLeft.setFillColor(sf::Color::Green);
    hudRight.setPosition(windowWidth-100, 0);
    hudRight.setFont(font);
    hudRight.setCharacterSize(40);
    hudRight.setFillColor(sf::Color::Red);

    
    ////////////////////////
    //MUSIC
    ///////////////////////
    
    // Load a music to play
    sf::Music sfxHit;
    sf::Music sfxPoint;
    if ((!sfxHit.openFromFile(resourcePath() + "magnum.ogg")) ||
          (!sfxPoint.openFromFile(resourcePath() + "wilhelm.ogg")))
    {
        return EXIT_FAILURE;
    }


    ////////////////////
    // GAME LOOP
    ////////////////////
    
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        
        //////////////////
        // GET INPUT
        ///////////////////
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && bat.getPosition().top > 0){
            bat.moveUp();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (bat.getPosition().top + bat.getPosition().height) <= windowHeight){
            bat.moveDown();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W ) && bat2.getPosition().top > 0){
            bat2.moveUp();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (bat2.getPosition().top + bat2.getPosition().height) <= windowHeight){
            bat2.moveDown();
        }

        
        /////////////////////////
        //COLLISION DETECTION
        ////////////////////////
        if(ball.getPosition().top > windowHeight){
            ball.reboundTopOrBottom();
            sfxHit.play();
        }
        if(ball.getPosition().top < 0){
            ball.reboundTopOrBottom();
            sfxHit.play();
        }
        if(ball.getPosition().left < 0 ){
            ball.hitSides();
            player2Score++;
            sfxPoint.play();
            
        }
        if((ball.getPosition().left + ball.getPosition().width) > windowWidth){
            ball.hitSides();
            player1Score++;
            sfxPoint.play();
        }
        if(ball.getPosition().intersects(bat.getPosition()) || ball.getPosition().intersects(bat2.getPosition())){
            ball.reboundBat();
            sfxHit.play();
        }
        
        /////////////////////////
        //UPDATE THE FRAME
        ////////////////////////
        bat.update();
        bat2.update();
        ball.update();
        stringPlayer1Score = std::to_string(player1Score);
        stringPlayer2Score = std::to_string(player2Score);
        
        /////////////////////////
        //DRAW THE FRAME
        ////////////////////////
    
        // Clear screen
        window.clear(sf::Color::Black);
        window.draw(bat.getShape());
        window.draw(bat2.getShape());
        window.draw(ball.getShape());

        // Draw the text/string stream
        hudLeft.setString(stringPlayer1Score);
        hudRight.setString(stringPlayer2Score);
        window.draw(hudLeft);
        window.draw(hudRight);

        // Update the window
        window.display();
        
        //manage framerates
        time1 += SKIP_TICKS;
        sleepTime = time1 - clock.getElapsedTime().asMilliseconds();
        if(sleepTime>=0){
            sf::sleep(sf::milliseconds(sleepTime));
        }
        
        
    }

    return EXIT_SUCCESS;
}
