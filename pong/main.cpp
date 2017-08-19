
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
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Pong");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    
    int score = 0;
    int lives = 3;
    
    //create game objects
    Bat bat (windowWidth-20, windowHeight/2);
    Bat bat2 (10, windowHeight/2);
    Ball ball(windowWidth/2,windowHeight/2);
    
    // Create text and a font
    sf::Text hud;
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    hud.setFont(font);
    hud.setCharacterSize(20);
    hud.setFillColor(sf::Color::White);

    /*
    // Load a music to play
    sf::Music music;
    if (!music.openFromFile(resourcePath() + "nice_music.ogg")) {
        return EXIT_FAILURE;
    }
    */
    
    /*// Load a sprite to display
     sf::Texture texture;
     if (!texture.loadFromFile(resourcePath() + "cute_image.jpg")) {
     return EXIT_FAILURE;
     }
     sf::Sprite sprite(texture);*/

    // Play the music
    //music.play();

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

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        
        /////////////////////////
        //Update the Frame
        ////////////////////////
        if(ball.getPosition().top > windowHeight){
            ball.reboundTopOrBottom();
        }
        if(ball.getPosition().top < 0){
            ball.reboundTopOrBottom();
        }
        if(ball.getPosition().left < 0 || (ball.getPosition().left + ball.getPosition().width) > windowWidth){
            ball.hitSides();
            if(lives>0) {
                lives--;
            }else{
                lives = 3;
            }
        }
        if(ball.getPosition().intersects(bat.getPosition()) || ball.getPosition().intersects(bat2.getPosition())){
            ball.reboundBat();
        }
        
        bat.update();
        bat2.update();
        ball.update();
        
        std::stringstream ss;
        ss << "Lives: " << lives;
        hud.setString(ss.str());
        
        /////////////////////////
        //Draw the Frame
        ////////////////////////
        
        
        // Clear screen
        window.clear(sf::Color::Black);
        window.draw(bat.getShape());
        window.draw(bat2.getShape());
        window.draw(ball.getShape());

        // Draw the sprite
        //window.draw(sprite);

        // Draw the string
        window.draw(hud);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
