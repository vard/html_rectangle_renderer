#include <iostream>

const int kCorrectArgCount = 3;


bool validateCommandLineArgs(int argc, char** argv) {
    if(argc != kCorrectArgCount){
        return false;
    }

    return true;
}


void printHelpMessage(){
    std::cout << "Usage: rectangle_html_renderer [input_file] [output_file]" << std::endl;
}


int main(int argc, char** argv) {
    if(!validateCommandLineArgs(argc, argv)){
        printHelpMessage();
        return 1;
    }

    const std::string inputFile{*(argv+1)};
    const std::string outputFile{*(argv+2)};
}
