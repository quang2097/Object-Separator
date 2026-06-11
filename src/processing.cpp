#include "../include/src/input.hpp"
#include "../include/src/output.hpp"
#include "../include/src/utils/announceError.hpp"
#include <filesystem>
#include <string>
#include <iterator>
#include <execution>
#include <vector>

namespace fs = std::filesystem;
using namespace std;
using namespace cv;

void processImage(Mat& image, const string& fileName);
string* resultLocationLocal;

int processing(std::string& dataLocation, std::string& resultLocation, int choice){
    vector<fs::path> imagePaths;
    string filename = "src/processing.cpp";
    resultLocationLocal = &resultLocation;

    if(choice == 1)
        resultLocation = dataLocation;

    int count = 0,
        countFailed = 0;

    if(!fs::exists(dataLocation)){
        cout << "Failed to find directory \'" + dataLocation + "\'." << endl
             << "Check locations.txt file." << endl;
        return 1;
    }

    for(const auto& entry : fs::directory_iterator(dataLocation)){
        if (entry.is_regular_file() && entry.path().extension() == ".jpg") {
            imagePaths.push_back(entry);
        } else{
            cout << "Failed to input file \'" << entry.path().string() << "\' " << "because of invalid file type. Continuing." << endl;
            announceError(28, filename);
        }
    }

    std::for_each(std::execution::par, imagePaths.begin(), imagePaths.end(), [](const fs::path& imagePath){
        Mat currentImage;
        string imagePathString = imagePath.string();

        int check = input(imagePathString, currentImage);

        if(check == 1){
            return;
        }

        processImage(currentImage, imagePath.filename().string());
        if(currentImage.empty()){
            cout << "Failed to process file \'" << imagePath << "\' " << "continuing." << endl;
            return;
        }
    });

    // for(const auto& entry : fs::directory_iterator(dataLocation)){
    //     Mat currentImage;
    //     string imagePath;

    //     if (entry.is_regular_file() && entry.path().extension() == ".jpg") {
    //         imagePath = entry.path().string();
    //     } else{
    //         cout << "Failed to input file \'" << imagePath << "\' " << "because of invalid file type. Continuing." << endl;
    //         announceError(28, filename);
    //     }

    //     int check = input(imagePath, currentImage);

    //     if(check == 1){
    //         countFailed++;
    //         continue;
    //     }

    //     processImage(currentImage);
    //     if(currentImage.empty()){
    //         cout << "Failed to process file \'" << imagePath << "\' " << "continuing." << endl;
    //         announceError(41, filename);
    //         countFailed++;
    //         continue;
    //     }

    //     output(resultLocation + "/" + entry.path().filename().string(), currentImage);
    //     count++;
    // }

    cout << "Successfully proccessed " << imagePaths.size() << " files." << endl;

    return imagePaths.size() == 0 ? 1 : 0;
}

//process the .jpg/.jpeg files.
void processImage(Mat& image, const string& fileName){
    output((*resultLocationLocal) + "/" + fileName, image);
}