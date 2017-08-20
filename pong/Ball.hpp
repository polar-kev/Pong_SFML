//
//  Ball.hpp
//  pong
//
//  Created by Kevin Semple on 2017-08-19.
//  Copyright © 2017 ksemp. All rights reserved.
//

#ifndef Ball_hpp
#define Ball_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

class Ball{
private:
    sf::Vector2f position;
    
    //A RectangleShap object called ref
    sf::RectangleShape ballShape;
    
    float xVelocity;
    float yVelocity;
    
public:
    Ball(float startX, float startY);
    sf::FloatRect getPosition();
    sf::RectangleShape getShape();
    float getXVelocity();
    float getYVelocity();
    void reboundTopOrBottom();
    void reboundBat();
    void hitSides();
    void update(float);
    
};

#endif /* Ball_hpp */
