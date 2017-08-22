//
//  Game.hpp
//  pong
//
//  Created by Kevin Semple on 2017-08-20.
//  Copyright © 2017 ksemp. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Bat.hpp"
#include "Ball.hpp"
// File path helper
#include "ResourcePath.hpp"

class Game{
private:
    static const int WINDOWWIDTH = 1024;
    static const int WINDOWHEIGHT = 768;
    static const int FRAMES_PER_SECOND = 60;
    const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;
    int sleepTime;
    int player1Score, player2Score;
    float time1;
    
    sf::Clock clock;
    
    sf::RenderWindow window;
    sf::Image icon;
    
    sf::Font font;
    sf::Text hudLeft;
    sf::Text hudRight;
    sf::Text fps;
    sf::Text winMessageP1;
    sf::Text winMessageP2;
    sf::Text introMessage;
    sf::Text pauseMessage;
    
    sf::Music sfxHit;
    sf::Music sfxPoint;
    
    Ball ball;
    Bat batLeft;
    Bat batRight;
    
    enum states {INTRO, PLAYING, P1_WIN, P2_WIN, PAUSED};
    
    int gameState;
    
    void getInput();
    void checkCollisions();
    void update();
    void draw();
    void handleEvents();
    void winConditionCheck();
    void resetGame();
    
public:
    Game();
    bool initialize();
    bool setup();
    void execute();
};
#endif /* Game_hpp */
