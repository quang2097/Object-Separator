#include "../include/libs/core.hpp"
#include "../include/src/utils/announceError.hpp"
#include <string>

using namespace std;
using namespace cv;

//input file via paths.
int input(const std::string& entry, cv::Mat& image){
    string filename = "src/input.cpp";
    image = imread(entry, IMREAD_COLOR);

    if(image.empty()){
        cout << "Failed to input file \'" << entry << "\'." << endl;
        announceError(15, filename);
        return 1;
    }

    return 0;
}