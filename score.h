#ifndef SCORE_H
#define SCORE_H

#include <stdlib.h>
#include <string>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

class score
{
    public:
        score(string position, string fontName, int size, sf::Vector2i windowResolution);
        void scoreIncrease();
        sf::Text displayValue;
        sf::Font font;
    protected:
    private:
};

#endif // SCORE_H
