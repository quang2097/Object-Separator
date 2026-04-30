#include "../include/libs/core.hpp"
#include "../include/src/utils/announceError.hpp"

using namespace std;
using namespace cv;

int save(string resultLocation, Mat& result){
    imwrite(resultLocation, result);
    return 1;
}

int output(std::string resultLocation, cv::Mat& result){
    int check = save(resultLocation, result);
    if(check == 0){
        cout << "Failed to save file at \'" << resultLocation << "\'.";
        announceError(19);
    }

    cout << "Save file at \'" << resultLocation << "\' " << "successful.";
    return 1;
}