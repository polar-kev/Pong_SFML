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

Ball::Ball(){
    reset();
}

void Ball::reset(){
    srand(time(NULL));
    int direction;
    int direction2;
    position.x = rand() % 100 + ((int)WINDOW_WIDTH/2) - 50;//modulo range + inital value
    position.y = rand() % (int)WINDOW_HEIGHT/2 + 1;//modulo range + inital value
    velocity.x = rand() % 10 + 5.2;
    velocity.y = rand() % 10 + 5.2;
    direction = rand() % 10 + 1;
    direction2 = rand() % 10 + 1;
    if(direction>5){velocity.x*=-1;}
    if(direction2>5){velocity.y*=-1;}
    
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
    //position.y -= (velocity.y * 1);
    //velocity.y++;
    velocity.y = -(velocity.y);
}


void Ball::reboundBat(){
    //position.x -= (velocity.x * 1);
    //velocity.x++;
    //velocity.y++;
    velocity.x = -(velocity.x*1.05);
}

void Ball::hitSides(){
    reset();
}

void Ball::update( ){
    //position += velocity;
    //ballShape.setPosition(position);
    ballShape.move(velocity);
}




