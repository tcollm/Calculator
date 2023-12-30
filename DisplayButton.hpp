#ifndef DISPLAY_BUTTON_HPP
#define DISPLAY_BUTTON_HPP

#include "Coordinate.hpp"
#include <SFML/Graphics.hpp>
#include <iostream> // for testing 

class DisplayButton {
private:
    const float WINDOW_X = 480.f;
    const float WINDOW_Y = 720.f;

    Coordinate _pos; // position
    Coordinate _size = {WINDOW_X, 90.f}; // the display button needs to be the length of the window
    sf::RectangleShape _shape; 

    std::string _textString;
    sf::Text _textShape; 
    float _textX;
    float _textY; 
    int _textSize = 36; 

    int _timesIntPressed = 0; 


    sf::Font _font; 

    int _integer = -1; // set to -1 until I implement negative numbers

public:
    DisplayButton(const float X_POS, const float Y_POS, const sf::Font& FONT);     
    
    void draw(sf::RenderWindow& window);
    void setText(const std::string TEXT); 
    // void deleteText();
    std::string getText();
    int getInt(); 
};


DisplayButton::DisplayButton(const float X_POS, const float Y_POS, const sf::Font& FONT) {
    // position stuff:
    _shape.setSize(sf::Vector2f(_size.x, _size.y)); // Set the size of the rectangle
    _pos = {X_POS, Y_POS}; // given pos from main
    _shape.setPosition(sf::Vector2f(_pos.x, _pos.y));

    // display color stuff:
    _shape.setFillColor(sf::Color::Black); 

    // text stuff:
    _font = FONT; 


    _textX = _textSize; // TEXT DISPLAYS ON THE FAR LEFT FOR TESTING
   
    // _textX = WINDOW_X - _textSize; // text displays on the far right    - (120.f / 2.f)
    _textY = _pos.y + (_size.y / 2.f) - (_textSize / 2.f); // display in the center of the rectnagle shape vertically

    _textShape.setCharacterSize(_textSize);
}


void DisplayButton::draw(sf::RenderWindow& window) {
    window.draw(_shape);
    _textShape.setString(_textString); 
    _textShape.setFont(_font); 
    _textShape.setPosition(sf::Vector2f(_textX, _textY));
    window.draw(_textShape);
}

void DisplayButton::setText(const std::string TEXT) {
    _textString = TEXT; 
    // if (_timesIntPressed > 1) {
    //     _textX -= (_textSize / 2); 
    // }
    _timesIntPressed++; 
    
}

// void DisplayButton::deleteText() {
//     if (_timesIntPressed > 3) {
//         _textX += (_textSize / 2); 
//         _timesIntPressed--;
//     }
// }

std::string DisplayButton::getText() {
    return _textString; 
}

int DisplayButton::getInt() {
    return _integer; 
}

#endif // DISPLAY_BUTTON_HPP