#include "AI.h"

AI::AI()
{
    //ctor
}

void AI::move(paddle &paddle, sf::Time time, sf::Vector2i windowResolution, ball &ball)
{
    //cout << goUp << "  " << paddle.shape.getPosition().y+paddle.shape.getGlobalBounds().height << "   " << windowResolution.y-10 << endl;
    //Checking when paddle whenever paddle needs to go up or down
    //cout << "ball position:" << ball.shape.getPosition().y << "    paddle center position:" << paddle.shape.getPosition().y+paddle.shape.getGlobalBounds().height/2 << endl;

    if(ball.shape.getPosition().y+20<(paddle.shape.getPosition().y+paddle.shape.getGlobalBounds().height/2))
        paddle.moveUp(time, paddleSpeed);
    else if(ball.shape.getPosition().y-20>(paddle.shape.getPosition().y+paddle.shape.getGlobalBounds().height/2))
        paddle.moveDown(time, windowResolution, paddleSpeed);

    //Checking if paddle needs to change direction
    /*if(paddle.shape.getPosition().y<10)
        goUp=0;
    else if(paddle.shape.getPosition().y+paddle.shape.getGlobalBounds().height>windowResolution.y-10)
        goUp=1;*/

}
