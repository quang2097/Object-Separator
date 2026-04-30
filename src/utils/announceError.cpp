#include <iostream>

void announceError(int lineNumber){
    std::cout << "Error at \'" << __FILE__ << "\' line " << lineNumber << "." << std::endl;
}