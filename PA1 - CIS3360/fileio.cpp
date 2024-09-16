#include <fstream>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>

namespace fs = std::filesystem;

int main(int argc, char* argv[]){
    // std::ofstream outf{ "sample.txt" };
    // if(!outf){
    //     std::cerr << "Error: Could not open sample.txt\n";
    //     return 1;
    // }

    // outf << "Hello world\n";
    // outf << "what is up troubler nation\n";

    std::ifstream file{ "sample.txt" };
    if(!file){
        std::cerr << "Error: sample.txt could not be opened for reading\n";
        return 1;
    }

    std::string str{};
    while(std::getline(file, str)){
        std::cout << str << '\n';
    }
    

    return 0;
}