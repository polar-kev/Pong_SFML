//
//  Bat.hpp
//  pong
//
//  Created by Kevin Semple on 2017-08-19.
//  Copyright © 2017 ksemp. All rights reserved.
//

#ifndef Bat_hpp
#define Bat_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

class Bat{
private:
    sf::Vector2f position;
    sf::RectangleShape batShape;
    float batSpeed;
    
public:
    Bat(float startX, float startY);
    sf::FloatRect getPosition();
    sf::RectangleShape getShape();
    void moveDown();
    void moveUp();
    void update();
};

#endif /* Bat_hpp */
