#include "../include/src/processing.hpp"
#include "../include/src/utils/readTxtFile.hpp"
#include <iostream>
#include <filesystem>

#if defined(_WIN32)
    #include <windows.h>
#elif defined(__linux__)
    #include <unistd.h>
#elif defined(__APPLE__)
    #include <mach-o/dyld.h>
#endif

namespace fs = std::filesystem;
using namespace std;

string getExecutablePath();
string getExecutableDirectory();

//this is main, duh :)
int main(){
    const string locationPath = getExecutableDirectory() + "/../locations.txt";
    vector<string> locations;
    string dataLocation, resultLocation;

    locations = readTxtFile(locationPath, 1);
    if(locations.size() < 2){
        cout << "locations.txt is invalid." << endl
             << "Please format the locations.txt file with the following example (ignore anything before the \':\'):"
             << "\nLine 1:C:/folder1/dataLocation"
             << "\nLine 2:C:/folder2/resultLocation"
             << "\nNote that each location is the name of a folder.";
        return 1;
    }

    dataLocation = locations[0];
    resultLocation = locations[1];

    int check = processing(dataLocation, resultLocation, 2);
    if(check == 1){
        cout << "Processing failed.";
        return 1;
    }

    cout << "Finished processing.";
    return 0;
}

//find path for the folder containing the executable file.
std::string getExecutablePath() {
    std::vector<char> buffer(1024);
    uint32_t size = buffer.size();

    //windows
    #if defined(_WIN32)
        DWORD len = GetModuleFileNameA(NULL, buffer.data(), static_cast<DWORD>(buffer.size()));
        if (len == 0) throw std::runtime_error("Failed to get executable path (Windows).");
        return std::filesystem::absolute(buffer.data()).string();

    //linux
    #elif defined(__linux__)
        ssize_t len = readlink("/proc/self/exe", buffer.data(), buffer.size() - 1);
        if (len == -1) throw std::runtime_error("Failed to get executable path (Linux).");
        buffer[len] = '\0';
        return std::filesystem::absolute(buffer.data()).string();

    //mac OS
    #elif defined(__APPLE__)
        if (_NSGetExecutablePath(buffer.data(), &size) != 0) {
            buffer.resize(size);
            if (_NSGetExecutablePath(buffer.data(), &size) != 0)
                throw std::runtime_error("Failed to get executable path (macOS).");
        }
        return std::filesystem::absolute(buffer.data()).string();

    //temple OS and others
    #else
        throw std::runtime_error("Unsupported platform.");
    #endif
}

//find the path of the executable file
std::string getExecutableDirectory() {
    return std::filesystem::path(getExecutablePath()).parent_path().string();
}