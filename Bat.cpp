//
//  Bat.cpp
//  pong
//
//  Created by Kevin Semple on 2017-08-19.
//  Copyright © 2017 ksemp. All rights reserved.
//

#include "Bat.hpp"

Bat::Bat(float startX, float startY){
    position.x = startX;
    position.y = startY;
    batSpeed = 0;
    
    batShape.setSize(sf::Vector2f(10, 300));
    batShape.setOutlineColor(sf::Color::White);
    batShape.setPosition(position);
}

sf::FloatRect Bat::getPosition(){
    return batShape.getGlobalBounds();
}

sf::RectangleShape Bat::getShape(){
    return batShape;
}

void Bat::moveDown(){
    batSpeed+=40;
}

void Bat::moveUp(){
    batSpeed-=40;
}

void Bat::update(){
    position.y += batSpeed;
    batShape.setPosition(position);
    batSpeed=0;
}
