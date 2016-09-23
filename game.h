#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "paddle.h"
#include "AI.h"
#include "ball.h"
#include "score.h"

class game
{
    public:
        game();
        void run(sf::Vector2i windowResolution);
        bool isOnePlayer=true;
        char paddleSize;
        int leftPaddleBallSpin=0, rightPaddleBallSpin=0;
        double ballSpeed;
    protected:
    private:
};

#endif // GAME_H
