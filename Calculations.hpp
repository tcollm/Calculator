#ifndef CALCULATIONS
#define CALCULATIONS

#include <string>

int Calculations (const int INTEGER_ONE, const int INTEGER_TWO, const std::string OPERATION) {
    int returnInt; 
    
    if (OPERATION == "+") {
        returnInt = INTEGER_ONE + INTEGER_TWO; 
    } else if (OPERATION == "-") {
        returnInt = INTEGER_ONE - INTEGER_TWO; 
    } else if (OPERATION == "x") {
        returnInt = INTEGER_ONE * INTEGER_TWO; 
    } else if (OPERATION == "/") {
        returnInt = INTEGER_ONE / INTEGER_TWO; 
    } else {
        
        returnInt = 10000; 
    }

    return returnInt; 
}


#endif // CALCULATIONS