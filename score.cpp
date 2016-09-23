#include "score.h"

score::score(string type, string fontName, int size, sf::Vector2i windowResolution)
{
    cout << "ctor started!" << endl;
    //Setting up score font
    if(!font.loadFromFile(fontName))
    {
        cout << "Unable to download font!!!" << endl;
    }
    displayValue.setString("0");
    displayValue.setFont(font);
    displayValue.setCharacterSize(size);

    //Setting up score position according to its type
    if(type == "left")
        displayValue.setPosition(windowResolution.x/2-windowResolution.x/4-displayValue.getGlobalBounds().width/2,windowResolution.y/4-displayValue.getGlobalBounds().height);
    else if(type == "right")
        displayValue.setPosition(windowResolution.x/2+windowResolution.x/4-displayValue.getGlobalBounds().width/2,windowResolution.y/4-displayValue.getGlobalBounds().height);

    displayValue.setColor(sf::Color(64,64,64));
}

void score::scoreIncrease()
{
    //Creates seperate variable for stoi function to work
    string displayValueString = displayValue.getString();

    //Converts string with score to int, increases value and than converts it back to string and loads it to sf::Text variable
    int scoreInt = stoi(displayValueString,nullptr,0);
    scoreInt++;
    displayValueString = std::to_string(scoreInt);
    displayValue.setString(displayValueString);
}
