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
    xVelocity = 50.0;
    yVelocity = 50.0;
    
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
    //position.y -= (yVelocity * 30);
    yVelocity = -yVelocity;
}

//TODO: Better physics calculation
void Ball::reboundBat(){
    //position.x -= (xVelocity * 30);
    xVelocity = -xVelocity;
}
    
void Ball::hitSides(){
    position.x = 500;
    position.y = 200;
}

void Ball::update(float elapsed){
    //position.x += xVelocity;
    //position.y += xVelocity;
    //ballShape.setPosition(position);
    ballShape.setPosition(position.x+elapsed*xVelocity,position.y+elapsed*xVelocity);
    ballShape.move(elapsed*xVelocity,elapsed*xVelocity);
}




