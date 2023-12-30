#include "Button.hpp"
#include "Coordinate.hpp"
#include "Calculations.hpp"
#include "VecToInt.hpp"
#include "DisplayButton.hpp"

#include <iostream> 
#include <vector>
#include <sstream>
using namespace std;

#include <SFML/Graphics.hpp>
using namespace sf;


int main() {
    float windowX = 480.f;
    float windowY = 720.f;
    const float SIZE_BUTTON_X = 120.f;
    const float SIZE_BUTTON_Y = 90.f;
    RenderWindow window( VideoMode(windowX, windowY), "Calculator" );

    Font font;
    if (!font.loadFromFile("RobotoFontFile/RobotoCondensed-Regular.ttf")) {
        cerr << "Error loading font." << endl;
        return EXIT_FAILURE;
    }

    // create objects:

    // 2d array of buttons
    const int ROWS = 4, COLS = 4;
    vector<vector<Button*>> buttonArray(ROWS, vector<Button*>(COLS));
    // create buttons
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            const float BUTTON_X = i * SIZE_BUTTON_X;
            const float BUTTON_Y = j * SIZE_BUTTON_Y + (windowY / 2); // buttons will be placed on bottom half of window
            buttonArray[i][j] = new Button(BUTTON_X, BUTTON_Y, font); 
        }
    }

    // set numbers 1 - 9:

    int num = 9; 
    for (int i = 0; i < 3; ++i) {
        int iNum = num - (1 * i); 
        for (int j = 0; j < 3; ++j) {
            int jNum = iNum - (3 * j);
            buttonArray[i][j]->setText(to_string(jNum)); 
        }
    }

    // set 0:
    buttonArray[0][3]->setText("0"); // CHANGE 0 to cover the bottom left and bottom second to left buttons 

    // set "+":
    buttonArray[3][3]->setText("+");  

    // set "-":
    buttonArray[3][2]->setText("-");

    // set "x":
    buttonArray[3][1]->setText("x"); 

    // set "/":
    buttonArray[3][0]->setText("/"); // CHANGE "/" position eventually

    // set "=":
    buttonArray[2][3]->setText("="); // CHANGE "=" position eventually

    // set delete:
    buttonArray[1][3]->setText("del"); 


    // set ".":
    // CHANGE this implementation later (will require both float and integers to be supported in the calculator math file)


    // display button:
    const float DISPLAY_BUTTON_X = 0; // display button covers entire window horizontally 
    const float DISPLAY_BUTTON_Y = 3 * SIZE_BUTTON_Y;

    DisplayButton* displayButton = new DisplayButton(DISPLAY_BUTTON_X, DISPLAY_BUTTON_Y, font); 
    displayButton->setText("0"); 

    // Create integer variables 

    vector<int> vInt1; 
    int integer1; 
    bool gotVInt1 = false; 
    bool tooLarge1 = false; 

    string operation; 
    bool gotOperation = false; 

    vector<int> vInt2; 
    int integer2;
    bool gotVInt2 = false; 
    bool tooLarge2 = false; 

    bool gotEquals = false; 

    int result; 

    bool dontDisplayOperation = false; 
    bool dontDisplayInt2 = false; 

 
    // perform any file processing once before draw loop begins


    Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            } else if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape) {
                    window.close();
                } else if (event.key.code == Keyboard::Q) {
                    window.close();
                }
            } else if (event.type == Event::MouseButtonPressed) {
                // if the left mouse button is pressed, check to see if the cursor is within the bounds of the day button
                // if it is within bounds, print out that number
                if (event.mouseButton.button == Mouse::Left) {
                    // check if the mouse is within bounds of any of the numbers
                    for (int i = 0; i < ROWS; ++i) {
                        for (int j = 0; j < COLS; ++j) {
                            if (buttonArray[i][j]->isMouseOver(window)) {
                                // // CHANGE: currently only one digit can be selected for each integer. Need to change it to a vector of integers, so that multiple digits may be selected
                                
                                if (buttonArray[i][j]->getInt() != -1 && !gotVInt1) { // append ints to vector1
                                    if (vInt1.size() < 9) {
                                        vInt1.push_back(buttonArray[i][j]->getInt()); 
                                        tooLarge1 = false; 
                                    } else {
                                        cerr << "Integer too large." << endl; 
                                        tooLarge1 = true; 
                                    }
                                
                                } else if (buttonArray[i][j]->getInt() != -1 && gotVInt1 && gotOperation && !(gotVInt2)) { // append ints to vector2
                                    if (vInt2.size() < 9) {
                                        vInt2.push_back(buttonArray[i][j]->getInt());
                                        tooLarge2 = false; 
                                    } else {
                                        cerr << "Integer too large." << endl; 
                                        tooLarge2 = true; 
                                    }

                                } else if (buttonArray[i][j]->getText() == "del" && !vInt1.empty() && !gotOperation) { // delete numbers from vector 1 if del pressed and vector is not empty and if operation has not already been pressed
                                    vInt1.pop_back();
                                    tooLarge1 = false; 
                                    // displayButton->deleteText(); 

                                // else if () {} // delete from v2
                                } else if (buttonArray[i][j]->getText() == "del" && !vInt2.empty() && !gotEquals) { // delete numbers from vector 2 if del pressed and vector 2 is not empty && equals has not already been pressed
                                    vInt2.pop_back();
                                    tooLarge2 = false; 
                                    // displayButton->deleteText(); 

                                } else if (buttonArray[i][j]->getInt() == -1 && !vInt1.empty() && buttonArray[i][j]->getText() != "del" && buttonArray[i][j]->getText() != "=" && !gotOperation && !gotEquals) { // append operation (delete is not an operation) if operation pressed and v1 not empty
                                    operation = buttonArray[i][j]->getText(); 
                                    gotVInt1 = true; 
                                    gotOperation = true; 

                                } else if (buttonArray[i][j]->getInt() == -1 && !vInt2.empty() && buttonArray[i][j]->getText() == "=" && gotVInt1 && gotOperation) {
                                    gotVInt2 = true; 
                                    gotEquals = true; 
                                }

                                // turn vectors into integers: 
                                if ( !(tooLarge1) ) {
                                    integer1 = VecToInt(vInt1); 
                                }
                                // cout << "Integer 1: " << integer1 << endl; 
                                if ( !(tooLarge2) ) {
                                    integer2 = VecToInt(vInt2); 
                                }
                                // cout << "Integer 2: " << integer2 << endl; 

                                if (gotEquals) {
                                    result = Calculations(integer1, integer2, operation); 
                                    dontDisplayInt2 = true;                      
                                    
                                    // cout << integer1 << " " << operation << " " << integer2 << " = " << result << endl;
                                }


                                if ( !(gotVInt1) ) { // display the first integer (do not display the operation)                                    
                                    // cout << "Integer 1: " << integer1 << endl;
                                    displayButton->setText( to_string(integer1) );

                                } else if ( gotOperation && buttonArray[i][j]->getInt() == -1 && !(dontDisplayOperation) ) { // got operation will always be true after operation pressed, so check if the int value is NOT that of int2 (also make sure that delete and "=" works)
                                    // cout << "Operation: " << operation << endl;
                                    displayButton->setText(operation); 
                                    dontDisplayOperation = true; 

                                } else if (!dontDisplayInt2) {
                                    // cout << "Integer 2: " << integer2 << endl; 
                                    displayButton->setText( to_string(integer2) );

                                } else {
                                    // cout << "Result: " << result << endl; 
                                    displayButton->setText( to_string(result) );
                                }

                                // reset everything: 
                                if (gotEquals) {
                                    gotVInt1 = false; 
                                    vInt1 = {0}; 
                                    integer1 = 0;

                                    gotOperation = false;
                                    operation = ""; 

                                    gotVInt2 = false; 
                                    vInt2 = {0}; 
                                    integer2 = 0; 

                                    gotEquals = false;

                                    dontDisplayOperation = false;
                                    dontDisplayInt2 = false; 
                                }





                            }
                        }
                    }
                } 
            }
        }



        window.clear(Color::Black);

        // place any draw commands here below:

        // draw all buttons
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                buttonArray[i][j]->draw(window); 
            }
        } 

        displayButton->draw(window);

        window.display();


    }
    // DELETE EVERYTHING: 

    return 0;
}
