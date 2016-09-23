#include "game.h"

AI ai;

game::game()
{
    //checking will this game be played with one or two players
    cout << "One or Two Player Game? (1/2): ";
    char isOnePlayerChar;
    do
    {
        isOnePlayerChar = getchar();
        if(isOnePlayerChar == '1')
        {
            isOnePlayer = true;
        }
        else if(isOnePlayerChar == '2')
        {
            isOnePlayer = false;
        }
    } while(isOnePlayerChar != '1' && isOnePlayerChar != '2');

    if(isOnePlayer == true)
    {
        char opponentDifficulty;
        cout << "Choose opponent difficulty (E/M/H/!): ";
        do
        {
            opponentDifficulty=getchar();
            if(opponentDifficulty == 'E' || opponentDifficulty == 'e')
                ai.paddleSpeed=0.3;
            if(opponentDifficulty == 'M' || opponentDifficulty == 'm')
                ai.paddleSpeed=0.6;
            if(opponentDifficulty == 'H' || opponentDifficulty == 'h')
                ai.paddleSpeed=0.8;
            if(opponentDifficulty == '!')
                ai.paddleSpeed=1.0;
        } while(opponentDifficulty != 'E' && opponentDifficulty != 'e' && opponentDifficulty != 'M' && opponentDifficulty != 'm' && opponentDifficulty != 'H' && opponentDifficulty != 'h' &&  opponentDifficulty != '!');
    }

    cout << "Small or Big paddle size? (S/B): ";
    do
    {
        paddleSize = getchar();

    }while(paddleSize != 'B' && paddleSize != 'b' && paddleSize != 'S' && paddleSize != 's');
}

void game::run(sf::Vector2i windowResolution)
{
    //creating window and paddles
    sf::RenderWindow window(sf::VideoMode(windowResolution.x,windowResolution.y),"Pong");
    paddle leftPaddle(windowResolution, "left", paddleSize);
    paddle rightPaddle(windowResolution, "right", paddleSize);
    ball ball(windowResolution);

    //Creating text that displays current score
    score leftScore("left","Digital.ttf",200,windowResolution);
    score rightScore("right","Digital.ttf",200,windowResolution);


    sf::Clock clock;
    sf::Time time;
    window.setFramerateLimit(120);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed)
            {
                switch(event.key.code)
                {
                    case sf::Keyboard::R:
                        ball.reset(windowResolution);
                        break;
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            rightPaddle.moveDown(time, windowResolution);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            rightPaddle.moveUp(time);
        }

        //moves ball and ai paddle
        if(isOnePlayer == true)
        {
            ai.move(leftPaddle, time, windowResolution, ball);
            //ai.move(rightPaddle, time, windowResolution, ball);
        }
        else
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                leftPaddle.moveUp(time);
                leftPaddleBallSpin=-1;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            {
                leftPaddle.moveDown(time, windowResolution);
                leftPaddleBallSpin=1;
            }
            else
                leftPaddleBallSpin=0;
        }
        ball.move(time);
        ball.checkCollisions(windowResolution, leftPaddle, rightPaddle, leftScore, rightScore, leftPaddleBallSpin, rightPaddleBallSpin);

        //checking elapsed time and printing framerate
        time = clock.getElapsedTime();
        clock.restart().asSeconds();
        //cout << 1.0f/time.asSeconds() << endl;

        window.clear();
        window.draw(leftPaddle.shape);
        window.draw(rightPaddle.shape);
        window.draw(leftScore.displayValue);
        window.draw(rightScore.displayValue);
        window.draw(ball.shape);
        window.display();
    }
}
