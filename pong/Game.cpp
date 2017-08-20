//
//  Game.cpp
//  pong
//
//  Created by Kevin Semple on 2017-08-20.
//  Copyright © 2017 ksemp. All rights reserved.
//

#include "Game.hpp"

Game::Game(){
    initialize();
    setup();
}//end of Game()

bool Game::initialize(){
    sleepTime = 0;
    player1Score = 0;
    player2Score = 0;
    time1 = clock.restart().asMilliseconds();;
    
    
    //Window parameters
    window.create(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "Pong");
    window.setVerticalSyncEnabled(true);
    //window.setFramerateLimit(100);
    
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return false;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    
    //Music
    if ((!sfxHit.openFromFile(resourcePath() + "magnum.ogg")) ||
        (!sfxPoint.openFromFile(resourcePath() + "wilhelm.ogg")))
    {
        return false;
    }
}//end of initialize()

bool Game::setup(){
    //Font and text
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return false;
    }
    
    hudLeft.setPosition(100, 0);
    hudLeft.setFont(font);
    hudLeft.setCharacterSize(40);
    hudLeft.setFillColor(sf::Color::Green);
    hudRight.setPosition(WINDOWWIDTH-100, 0);
    hudRight.setFont(font);
    hudRight.setCharacterSize(40);
    hudRight.setFillColor(sf::Color::Red);
    
    batLeft.setPosition(20, WINDOWHEIGHT/2);
    batRight.setPosition(WINDOWWIDTH-50, WINDOWHEIGHT/2);
    
    gameState = states::INTRO;
}//end of setup()

void Game::execute(){
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && batRight.getPosition().top > 0){
            batRight.moveUp();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (batRight.getPosition().top + batRight.getPosition().height) <= WINDOWHEIGHT){
            batRight.moveDown();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W ) && batLeft.getPosition().top > 0){
            batLeft.moveUp();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (batLeft.getPosition().top + batLeft.getPosition().height) <= WINDOWHEIGHT){
            batLeft.moveDown();
        }
        
        
        /////////////////////////
        //COLLISION DETECTION
        ////////////////////////
        if(ball.getPosition().top > WINDOWHEIGHT){
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
        if((ball.getPosition().left + ball.getPosition().width) > WINDOWWIDTH){
            ball.hitSides();
            player1Score++;
            sfxPoint.play();
        }
        if(ball.getPosition().intersects(batLeft.getPosition()) || ball.getPosition().intersects(batRight.getPosition())){
            ball.reboundBat();
            sfxHit.play();
        }
        
        /////////////////////////
        //UPDATE THE FRAME
        ////////////////////////
        batLeft.update();
        batRight.update();
        ball.update();
        hudLeft.setString(std::to_string(player1Score));
        hudRight.setString(std::to_string(player2Score));
        
        /////////////////////////
        //DRAW THE FRAME
        ////////////////////////
        
        // Clear screen
        window.clear(sf::Color::Black);
        window.draw(batLeft.getShape());
        window.draw(batRight.getShape());
        window.draw(ball.getShape());
        
        // Draw the text/string stream
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
    }//end of while loop
}//end of execute()






