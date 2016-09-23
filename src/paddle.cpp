#include "paddle.h"

paddle::paddle(sf::Vector2i windowResolution, string positionDeterminant, char paddleSize)
{
    //setting paddle size
    size.x=windowResolution.x/64;
    if(paddleSize == 'B' || paddleSize == 'b')
        size.y=windowResolution.y/4;
    else
        size.y=windowResolution.y/8;
    shape.setSize(size);

    //setting paddle position
    if(positionDeterminant=="left")
        shape.setPosition(size.x, windowResolution.y/2-shape.getGlobalBounds().height/2);
    else if(positionDeterminant=="right")
        shape.setPosition(windowResolution.x-size.x*2, windowResolution.y/2-shape.getGlobalBounds().height/2);
}


void paddle::moveUp(sf::Time time, double speed)
{
    //cout << "Function moveUp was called" << endl;
    if(shape.getPosition().y>8)
        //sth is wrong over here
        shape.move(sf::Vector2f(0,-4*speed*time.asMilliseconds()/4));
    //cout << time.asMilliseconds() << endl;
}

void paddle::moveDown(sf::Time time, sf::Vector2i windowResolution, double speed)
{
    if(shape.getPosition().y+size.y<windowResolution.y-8)
        shape.move(sf::Vector2f(0,4*speed*time.asMilliseconds()/4));
}
