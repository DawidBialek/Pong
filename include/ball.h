#ifndef BALL_H
#define BALL_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <fstream>
#include "paddle.h"
#include "score.h"

using namespace std;

class ball
{
    public:
        ball(sf::Vector2i windowResolution);
        void checkCollisions(sf::Vector2i windowResolution, paddle &leftPaddle, paddle &rightPaddle, score &leftScore, score &rightScore, int leftPaddleBallSpin, int rightPaddleBallSpin);
        void setBallSpin(sf::Vector2f &previousActivePaddlePosition, sf::Vector2f &currentActivePaddlePosition, int &activePaddleBallSpin);
        void ballBounce(paddle &activePaddle, int paddleBallSpin);
        void move(sf::Time time);
        void reset(sf::Vector2i windowResolution);
        sf::CircleShape shape;
        //bool goLeft=0, goUp=1;
        sf::Vector2f speedVector=sf::Vector2f(1.f,1.f), previousLeftPaddlePosition=sf::Vector2f(0.f,0.f), currentLeftPaddlePosition=sf::Vector2f(0.f,0.f),previousRightPaddlePosition=sf::Vector2f(0.f,0.f), currentRightPaddlePosition=sf::Vector2f(0.f,0.f);
        sf::Vector2f ballHitPoit, previousBallPosition=sf::Vector2f(0.f,0.f), currentBallPosition=sf::Vector2f(0.f,0.f), middleBallPosition=sf::Vector2f(0.f,0.f);
        sf::Sound ballHitSound, playerScoredSound;
        sf::SoundBuffer ballPaddleHitSoundBuffer, playerScoredSoundBuffer;
        int ballWallBounceCooldown=0, ballPaddleBounceCooldown=0;
        double ballSpeedIncreaseFactor=1.5;
        double ballSpeed;
    protected:
    private:
};

#endif // BALL_H
