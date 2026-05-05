#include "../../include/src/utils/announceError.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

inline void processAddress(std::string& address){
    for(char& c:address){
        if(c == '\\') c = '/';
    }
}

//it is what I say it is.
std::vector<std::string> readTxtFile(const std::string& filename){
    std::string localFilename = "src/utils/readTxtFile.cpp";
    std::vector<std::string> strings;
    std::fstream file(filename);

    if(!file.is_open()){
        std::cout << "Failed to find \'" << filename << "\'" << std::endl;
        announceError(13, localFilename);
        return {};
    }

    std::string line;
    while(std::getline(file, line)){
        strings.emplace_back(line);
    }

    file.close();

    return strings;
}

std::vector<std::string> readTxtFile(const std::string& filename, const int type){
    std::string localFilename = "src/utils/readTxtFile.cpp";
    std::vector<std::string> strings;
    std::fstream file(filename);

    if(!file.is_open()){
        std::cout << "Failed to find \'" << filename << "\'" << std::endl;
        announceError(13, localFilename);
        return {};
    }

    std::string line;
    while(std::getline(file, line)){
        if(type == 1) processAddress(line);
        strings.emplace_back(line);
    }

    file.close();

    return strings;
}