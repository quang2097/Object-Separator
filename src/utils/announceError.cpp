#include <iostream>

//print error message with the line the error ocurred. Very tedious -_-
void announceError(const int lineNumber, const std::string& filename){
    std::cout << "Error at \'" << filename << "\' line " << lineNumber << "." << std::endl;
}