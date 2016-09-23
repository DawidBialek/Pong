#ifndef AI_H
#define AI_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "paddle.h"
#include "ball.h"

using namespace std;

class AI
{
    public:
        AI();
        void move(paddle &paddle, sf::Time time, sf::Vector2i windowResolution, ball &ball);
        //bool goUp=1;
        double paddleSpeed=0;
    protected:
    private:
};

#endif // AI_H
