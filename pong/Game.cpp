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
    resetGame();
    setup();
}//end of Game()

bool Game::initialize(){
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
    
    setup();
    
    return true;
}//end of initialize()

bool Game::setup(){
    //setup font
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return false;
    }
    sleepTime = 0;
    
    //setup text
    hudLeft.setPosition(100, 0);
    hudLeft.setFont(font);
    hudLeft.setCharacterSize(40);
    hudLeft.setFillColor(sf::Color::Green);
    hudRight.setPosition(WINDOWWIDTH-100, 0);
    hudRight.setFont(font);
    hudRight.setCharacterSize(40);
    hudRight.setFillColor(sf::Color::Red);
    
    introMessage.setString("PONGx\nPress any key to begin.");
    introMessage.setFont(font);
    introMessage.setCharacterSize(40);
    introMessage.setFillColor(sf::Color::White);
    
    winMessageP1.setString("Player 1 Wins");
    winMessageP1.setFont(font);
    winMessageP1.setCharacterSize(40);
    winMessageP1.setFillColor(sf::Color::White);
    
    winMessageP2.setString("Player 2 Wins");
    winMessageP2.setFont(font);
    winMessageP2.setCharacterSize(40);
    winMessageP2.setFillColor(sf::Color::White);
    
    pauseMessage.setString("Paused");
    pauseMessage.setFont(font);
    pauseMessage.setCharacterSize(40);
    pauseMessage.setFillColor(sf::Color::White);
    
    //resetGame();
    gameState = states::INTRO;

}//end of setup()

void Game::execute(){
    // Start the game loop
    while (window.isOpen())
    {
        handleEvents();
        getInput();
        checkCollisions();
        winConditionCheck();
        update();
        draw();
        
        //manage framerates
        time1 += SKIP_TICKS;
        sleepTime = time1 - clock.getElapsedTime().asMilliseconds();
        if(sleepTime>=0){
            sf::sleep(sf::milliseconds(sleepTime));
        }
    }//end of while loop
}//end of execute()


void Game::getInput(){
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
}//end of getInput()

void Game::checkCollisions(){
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
}//end of checkCollisions()

void Game::update(){
    switch(gameState){
        case states::INTRO:
            break;
        case states::PLAYING:
            batLeft.update();
            batRight.update();
            ball.update();
            //update score
            hudLeft.setString(std::to_string(player1Score));
            hudRight.setString(std::to_string(player2Score));
            break;
        case states::P1_WIN:
            break;
        case states::P2_WIN:
            break;
        case states::PAUSED:
            break;
        default:
            break;
    }
}//end of update()

void Game::draw(){
    // Clear screen
    window.clear(sf::Color::Black);
    
    switch(gameState){
        case states::INTRO:
            window.draw(introMessage);
            break;
        case states::PLAYING:
            window.draw(batLeft.getShape());
            window.draw(batRight.getShape());
            window.draw(ball.getShape());
            
            // Draw the text/string stream
            window.draw(hudLeft);
            window.draw(hudRight);
            break;
        case states::P1_WIN:
            window.draw(winMessageP1);
            break;
        case states::P2_WIN:
            window.draw(winMessageP2);
            break;
        case states::PAUSED:
            window.draw(pauseMessage);
            break;
        default:
            break;
    }
    // Update the window
    window.display();
}//end of draw()

void Game::handleEvents(){
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
        } else if(gameState == states::INTRO && event.type == sf::Event::KeyPressed){
            resetGame();
            gameState = states::PLAYING;
        }else if(gameState == states::PLAYING && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P){
            gameState = states::PAUSED;
        }else if(gameState == states::PAUSED && event.type == sf::Event::KeyPressed){
            gameState = states::INTRO;
        } else if((gameState == states::P1_WIN || gameState == states::P2_WIN) && event.type == sf::Event::KeyPressed){
            resetGame();
            gameState = states::INTRO;
        }
    }//end of while
}//end of handleEvents()

void Game::winConditionCheck(){
    if(player1Score >= 2 && player1Score >= player2Score + 2){
        gameState=states::P1_WIN;
    } else if(player2Score >= 2 && player2Score >= player1Score + 2){
        gameState=states::P2_WIN;
    }
}//end of winConditionCheck()

void Game::resetGame(){
    batLeft.setPosition(20, WINDOWHEIGHT/2);
    batRight.setPosition(WINDOWWIDTH-50, WINDOWHEIGHT/2);
    player1Score = 0;
    player2Score = 0;
}//end of resetGame()
