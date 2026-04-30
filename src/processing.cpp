#include "../include/src/input.hpp"
#include "../include/src/output.hpp"
#include "../include/src/utils/announceError.hpp"
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;
using namespace cv;

void processImage(Mat& image){
    if(image.empty())
        return;
}

int processing(std::string& dataLocation, std::string& resultLocation, int choice){
    if(choice == 1)
        resultLocation = dataLocation;

    int count = 0,
        countFailed = 0;

    for(const auto& entry : fs::directory_iterator(dataLocation)){
        Mat currentImage;
        string imagePath;

        if (entry.is_regular_file() && entry.path().extension() == ".jpg") {
            imagePath = entry.path().string();
        } else{
            cout << "Failed to input file \'" << imagePath << "\' " << "because of invalid file type. Continuing." << endl;
            announceError(30);
        }

        int check = input(imagePath, currentImage);

        if(check == 0){
            countFailed++;
            continue;
        }

        processImage(currentImage);
        if(currentImage.empty()){
            cout << "Failed to process file \'" << imagePath << "\' " << "continuing." << endl;
            announceError(43);
            countFailed++;
            continue;
        }

        output(resultLocation + "/" + entry.path().filename().string(), currentImage);
        count++;
    }

    cout << "Successfully proccessed " << count << " files." << endl;
    cout << "Failed to proccess " << countFailed << " files." << endl;

    return count == 0 ? 0 : 1;
}