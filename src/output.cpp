#include "../include/libs/core.hpp"
#include "../include/src/utils/announceError.hpp"
#include <string>

using namespace std;
using namespace cv;

int save(const string& resultLocation, Mat& result);

int output(const std::string& resultLocation, cv::Mat& result){
    string filename = "src/output.cpp";
    int check = save(resultLocation, result);
    if(check == 1){
        cout << "Failed to save file at \'" << resultLocation << "\'.";
        announceError(14, filename);
    }

    cout << "Save file at \'" << resultLocation << "\' " << "successful.";
    return 0;
}

//save file.
int save(const string& resultLocation, Mat& result){
    imwrite(resultLocation, result);
    return 0;
}