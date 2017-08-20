//
//  Ball.cpp
//  pong
//
//  Created by Kevin Semple on 2017-08-19.
//  Copyright © 2017 ksemp. All rights reserved.
//

#include "Ball.hpp"
#include <stdlib.h>
#include <time.h>
#include "Globals.h"

Ball::Ball(float startX, float startY){
    position.x = startX;
    position.y = startY;
    xVelocity = 50.0;
    yVelocity = 50.0;
    
    ballShape.setSize(sf::Vector2f(10, 10));
    ballShape.setOutlineColor(sf::Color::White);
    ballShape.setPosition(position);
}

sf::FloatRect Ball::getPosition(){
    return ballShape.getGlobalBounds();
}

sf::RectangleShape Ball::getShape(){
    return ballShape;
}

sf::Vector2f Ball::getVelocity() const{
    return velocity;
}

//TODO: Implement swept path collision detection
void Ball::reboundTopOrBottom(){
    //position.y -= (yVelocity * 30);
    yVelocity = -yVelocity;
}


void Ball::reboundBat(){
    //position.x -= (xVelocity * 30);
    xVelocity = -xVelocity;
}
    
void Ball::hitSides(){
    reset();
}

void Ball::update(float elapsed){
    //position.x += xVelocity;
    //position.y += xVelocity;
    //ballShape.setPosition(position);
    ballShape.setPosition(position.x+elapsed*xVelocity,position.y+elapsed*xVelocity);
    ballShape.move(elapsed*xVelocity,elapsed*xVelocity);
}




