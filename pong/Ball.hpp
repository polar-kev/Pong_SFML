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
    sf::Vector2f velocity;
    
    //A RectangleShap object called ref
    sf::RectangleShape ballShape;
    
public:
    Ball();
    sf::FloatRect getPosition();
    sf::RectangleShape getShape();
    sf::Vector2f getVelocity() const;
    void reboundTopOrBottom();
    void reboundBat();
    void hitSides();
    void update();
    void reset();
    
};

#endif /* Ball_hpp */
