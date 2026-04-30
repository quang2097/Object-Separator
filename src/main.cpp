#include "../include/src/processing.hpp"
#include <iostream>

using namespace std;

int main(){
    string dataLocation = "", resultLocation = "";

    cout << "Type in data location: ";
    cin >> dataLocation;

    cout << "Type in resultLocation: ";
    cin >> resultLocation;

    int choice = 0;
    cout << "Choose how to proceed:\n1:replace current data files (delete original)\n2:place result into result location picked (place result in new folder)\nelse:exit\n\n";
    cin >> choice;
    if(choice < 1 || choice > 2){
        cout << "Exited by choice.";
        return 0;
    }

    int check = processing(dataLocation, resultLocation, choice);
    if(check == 0){
        cout << "Processing failed.";
        return 0;
    }

    cout << "Finished processing.";
    return 1;
}