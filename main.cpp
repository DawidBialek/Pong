#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "include/game.h"

using namespace std;

int main()
{
    game game;
    game.run(sf::Vector2i(1280,720));
    return 0;
}
