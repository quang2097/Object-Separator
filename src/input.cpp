#include "../include/libs/core.hpp"
#include "../include/src/utils/announceError.hpp"

using namespace std;
using namespace cv;

int input(std::string& entry, cv::Mat& image){
    Mat currentImage = imread(entry, IMREAD_COLOR);

    if(currentImage.empty()){
        cout << "Failed to input file \'" << entry << "\'." << endl;
        announceError(16);
        return 0;
    }

    image = currentImage.clone();

    return 1;
}