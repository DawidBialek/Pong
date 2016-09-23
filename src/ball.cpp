#include "ball.h"

ball::ball(sf::Vector2i windowResolution)
{
    srand(time(NULL));
    shape.setPosition(windowResolution.x/2-shape.getGlobalBounds().width, windowResolution.y/2-shape.getGlobalBounds().height);
    shape.setFillColor(sf::Color::White);
    shape.setRadius(20);
    do
    {
        speedVector.x=rand()%3-1;
    }
    while(speedVector.x==0);

    //sound related stuff
    if(!ballPaddleHitSoundBuffer.loadFromFile("BallHitSound.wav"))
       cout << "Error occurred while loading ballPaddleHitSoundBuffer!" << endl;
    if(!playerScoredSoundBuffer.loadFromFile("PlayerScoredSound.wav"))
        cout << "Error occurred while loading PlayerScoredSound!" << endl;
    ballHitSound.setBuffer(ballPaddleHitSoundBuffer);
    ballHitSound.setVolume(50);
    playerScoredSound.setBuffer(playerScoredSoundBuffer);
    playerScoredSound.setVolume(50);

    ballSpeed=0;
}

void ball::reset(sf::Vector2i windowResolution)
{
    shape.setPosition(windowResolution.x/2-shape.getGlobalBounds().width, windowResolution.y/2-shape.getGlobalBounds().height);
    do
    {
        speedVector.x=rand()%3-1;
    }
    while(speedVector.x==0);
    ballSpeedIncreaseFactor=1.5;
    speedVector.y=1.0f;
    playerScoredSound.play();
}

void ball::ballBounce(paddle &activePaddle, int paddleBallSpin)
{
        ballHitPoit.y=(shape.getPosition().y+shape.getRadius()-(activePaddle.shape.getPosition().y+activePaddle.shape.getGlobalBounds().height/2))/100;


        speedVector.x*=ballSpeedIncreaseFactor*-1;   //changes ball speed after hitting the paddle
        speedVector.y=ballHitPoit.y*3.5+paddleBallSpin*2.5;

        //changes the way ballSpeedIncreaseFactor value increases depending on ballSpeed
        if(ballSpeed<=12)
            ballSpeedIncreaseFactor=sqrt(ballSpeedIncreaseFactor)*1.04;
        else if(ballSpeed>12 && ballSpeed<25)
            ballSpeedIncreaseFactor=sqrt(ballSpeedIncreaseFactor)*1.02;
        else if(ballSpeed>=25 && ballSpeed<32)
            ballSpeedIncreaseFactor=sqrt(ballSpeedIncreaseFactor)*1.01;
        else if(ballSpeed>=32 && ballSpeed<38)
            ballSpeedIncreaseFactor=sqrt(ballSpeedIncreaseFactor)*1.005;
        else if(ballSpeed<39)
            ballSpeedIncreaseFactor=sqrt(ballSpeedIncreaseFactor);
        else ballSpeedIncreaseFactor=1;

        /*if(ballSpeedIncreaseFactor>=1.105)
            ballSpeedIncreaseFactor=sqrt(ballSpeedIncreaseFactor)*1.05;
        else if(ballSpeedIncreaseFactor>=1.0862)
            ballSpeedIncreaseFactor=sqrt(ballSpeedIncreaseFactor)*1.042;
        else if(ballSpeedIncreaseFactor>=1.055)
            ballSpeedIncreaseFactor=sqrt(ballSpeedIncreaseFactor)*1.026;
        else if(ballSpeedIncreaseFactor>=1.03)
            ballSpeedIncreaseFactor=sqrt(ballSpeedIncreaseFactor)*1.014;*/

        cout << "ballSpeedIncreaseFactor: " << ballSpeedIncreaseFactor << " ballSpeed: " << abs(ballSpeed) << endl;
        ballWallBounceCooldown=0;
        ballPaddleBounceCooldown=10;

        ballHitSound.setPitch(speedVector.x/4);
        ballHitSound.play();
}

void ball::setBallSpin(sf::Vector2f &previousActivePaddlePosition, sf::Vector2f &currentActivePaddlePosition, int &activePaddleBallSpin)
{
    //if paddle moved up
    if(previousActivePaddlePosition.y>currentActivePaddlePosition.y)
        activePaddleBallSpin=-1;
    //if paddle moved down
    else if(previousActivePaddlePosition.y<currentActivePaddlePosition.y)
        activePaddleBallSpin=1;
    //else set to no spin
    else
        activePaddleBallSpin=0;
}

void ball::checkCollisions(sf::Vector2i windowResolution, paddle &leftPaddle, paddle &rightPaddle, score &leftScore, score &rightScore, int leftPaddleBallSpin, int rightPaddleBallSpin)
{
    //Compares paddle posistions to tell if ball should be spinned
    if(previousRightPaddlePosition.y != currentRightPaddlePosition.y)
    {
        setBallSpin(previousRightPaddlePosition, currentRightPaddlePosition, rightPaddleBallSpin);
    }
    if(previousLeftPaddlePosition.y != currentLeftPaddlePosition.y)
    {
        setBallSpin(previousLeftPaddlePosition, currentLeftPaddlePosition, leftPaddleBallSpin);
    }

    previousLeftPaddlePosition.y=currentLeftPaddlePosition.y;
    currentLeftPaddlePosition.y=leftPaddle.shape.getPosition().y;

    previousRightPaddlePosition.y=currentRightPaddlePosition.y;
    currentRightPaddlePosition.y=rightPaddle.shape.getPosition().y;

    //gets additional point between ball pos from previous frame and currnet frame when ballSpeed is higher than 40
    if(abs(ballSpeed)>60)
    {
        previousBallPosition.x=currentBallPosition.x;
        currentBallPosition.x=shape.getPosition().x;
        middleBallPosition.x=(previousBallPosition.x+currentBallPosition.x)/2;
    }

    //checks for collisions with paddles if ballPaddleBounceCooldown is equal to zero
    if(ballPaddleBounceCooldown == 0)
    {
        if (abs(ballSpeed)>60)
        {
            if(previousBallPosition.x-currentBallPosition.x<0)
            {
                //cout << "right" << endl;
                if(shape.getGlobalBounds().intersects(rightPaddle.shape.getGlobalBounds()) || shape.getPosition().x<=middleBallPosition.x && shape.getPosition().x+shape.getRadius()>=middleBallPosition.x)
                    this->ballBounce(rightPaddle, rightPaddleBallSpin);
                else if(shape.getGlobalBounds().intersects(rightPaddle.shape.getGlobalBounds()) || shape.getPosition().x<=middleBallPosition.x && shape.getPosition().x+shape.getRadius()>=middleBallPosition.x)
                    this->ballBounce(leftPaddle, leftPaddleBallSpin);
            }
            else if(previousBallPosition.x-currentBallPosition.x>0)
            {
                //cout << "left" << endl;
                if(shape.getGlobalBounds().intersects(rightPaddle.shape.getGlobalBounds()) || shape.getPosition().x>=middleBallPosition.x && shape.getPosition().x-shape.getRadius()<=middleBallPosition.x)
                    this->ballBounce(rightPaddle, rightPaddleBallSpin);
                else if(shape.getGlobalBounds().intersects(rightPaddle.shape.getGlobalBounds()) || shape.getPosition().x>=middleBallPosition.x && shape.getPosition().x-shape.getRadius()<=middleBallPosition.x)
                    this->ballBounce(leftPaddle, leftPaddleBallSpin);
            }
        }
        else if(shape.getGlobalBounds().intersects(rightPaddle.shape.getGlobalBounds()))
            this->ballBounce(rightPaddle, rightPaddleBallSpin);
        else if(shape.getGlobalBounds().intersects(leftPaddle.shape.getGlobalBounds()))
            this->ballBounce(leftPaddle, leftPaddleBallSpin);
    }

    //checks for collisions with walls
    if(shape.getPosition().y<=0 && ballWallBounceCooldown==0 || shape.getPosition().y>=windowResolution.y-shape.getGlobalBounds().height && ballWallBounceCooldown==0)
    {
        speedVector.y*=-1;
        ballWallBounceCooldown=25;
    }
    else if(shape.getPosition().x<=0)
    {
        rightScore.scoreIncrease();
        this->reset(windowResolution);
    }
    else if(shape.getPosition().x>=windowResolution.x-shape.getGlobalBounds().width)
    {
        leftScore.scoreIncrease();
        this->reset(windowResolution);
    }
    if(ballWallBounceCooldown>0)
        ballWallBounceCooldown--;
    if(ballPaddleBounceCooldown>0){
        ballPaddleBounceCooldown--;
    }
}

void ball::move (sf::Time time)
{
    //moves the ball
    shape.move(speedVector.x*time.asMilliseconds()/4,speedVector.y*time.asMilliseconds()/4);
    ballSpeed=abs(speedVector.x*time.asMilliseconds()/4);
    //cout << speedVector.x*time.asMilliseconds()/4 << endl;
}
