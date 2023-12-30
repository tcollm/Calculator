#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Coordinate.hpp"
#include <SFML/Graphics.hpp>

class Button {
private:
    Coordinate _pos; // position
    Coordinate _size = {120.f, 90.f}; 
    // temporary size: 
    // X = 3/4 the size of the height. 4 Buttons will be placed horizontally, there will be space between the buttons. 
    // Y = half the window will be for inputting numbers, so the bottom half will be buttons. The (bottom half of the) window will fit 4 buttons vertically. 
    sf::RectangleShape _shape; 
    std::string _textString;
    sf::Text _textShape; 
    sf::Font _font; 
    int _integer = -1; // set to -1 until I implement negative numbers

    const float WINDOW_X = 480.f;
    const float WINDOW_Y = 720.f;

    bool isInteger(const std::string STR) {
        if (STR == "+" || STR == "-" || STR == "x" || STR == "/" || STR == "=" || STR == "del") { // adjust for any NON-INT buttons
            return false; 
        } else {
            return true; 
        }
    }


public:
    Button(const float X_POS, const float Y_POS, const sf::Font& FONT); 
    // ~Button();
    
    
    void draw(sf::RenderWindow& window);
    void setText(const std::string TEXT); 
    std::string getText();
    int getInt(); 
    bool isMouseOver(sf::RenderWindow& window);
};


Button::Button(const float X_POS, const float Y_POS, const sf::Font& FONT) {
    // position stuff:
    _shape.setSize(sf::Vector2f(_size.x, _size.y)); // Set the size of the rectangle
    _pos = {X_POS, Y_POS}; // given pos from main
    _shape.setPosition(sf::Vector2f(_pos.x, _pos.y));

    // display color stuff:
    _shape.setFillColor(sf::Color(64,64,64)); // dark gray
    _shape.setOutlineColor(sf::Color::Black);
    _shape.setOutlineThickness(2.0f);

    // text stuff:
    _font = FONT; 
    float textX = _pos.x + (_size.x / 2.f); // center the x (can't get it perfectly centered FIX LATER)
    float textY = _pos.y + (_size.y / 2.f); // center the y (can't get it perfectly centered FIX LATER)
    _textShape.setPosition(sf::Vector2f(textX, textY));
}


void Button::draw(sf::RenderWindow& window) {
    window.draw(_shape);
    _textShape.setString(_textString); 
    _textShape.setFont(_font); 
    window.draw(_textShape);
}

void Button::setText(const std::string TEXT) {
    _textString = TEXT; 
    if (isInteger(TEXT)) {
        _integer = std::stoi(TEXT);
    } else {
        _integer = -1; // CHANGE when I implement negative numbers
    }
}

std::string Button::getText() {
    return _textString; 
}

int Button::getInt() {
    return _integer; 
}

bool Button::isMouseOver(sf::RenderWindow& window) {
    // map the mouse position to the window, then get the bounds of the button shape and see if the mouse pos is within the button shape pos
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mappedMousePos = window.mapPixelToCoords(mousePos);
    return _shape.getGlobalBounds().contains(mappedMousePos);
}

#endif // BUTTON_HPP