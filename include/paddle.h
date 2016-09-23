#ifndef PADDLE_H
#define PADDLE_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace std;

class paddle
{
    public:
        paddle(sf::Vector2i windowResolution, string positionDeterminant, char paddleSize);
        void moveUp(sf::Time time, double speed=1);
        void moveDown(sf::Time time, sf::Vector2i windowResolution, double speed=1);
        sf::Vector2f size;
        sf::RectangleShape shape;
    protected:
    private:
};

#endif // PADDLE_H
