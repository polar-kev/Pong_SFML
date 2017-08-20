//
//  Ball.cpp
//  pong
//
//  Created by Kevin Semple on 2017-08-19.
//  Copyright © 2017 ksemp. All rights reserved.
//

#include "Ball.hpp"

Ball::Ball(float startX, float startY){
    position.x = startX;
    position.y = startY;
    xVelocity = 20.2f;
    yVelocity = 20.2f;
    
    ballShape.setSize(sf::Vector2f(10, 10));
    ballShape.setOutlineColor(sf::Color::White);
}

sf::FloatRect Ball::getPosition(){
    return ballShape.getGlobalBounds();
}

sf::RectangleShape Ball::getShape(){
    return ballShape;
}

float Ball::getXVelocity(){
    return xVelocity;
}

float Ball::getYVelocity(){
    return yVelocity;
}

void Ball::reboundTopOrBottom(){
    position.y -= (yVelocity * 1);
    yVelocity = -yVelocity;
}

//TODO: Better physics calculation
void Ball::reboundBat(){
    position.x -= (xVelocity * 1);
    xVelocity = -xVelocity;
}
    
void Ball::hitSides(){
    position.x = 500;
    position.y = 200;
}

void Ball::update( ){
    position.x += xVelocity;
    position.y += yVelocity;
    ballShape.setPosition(position);
}




