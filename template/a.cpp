#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <format>

int read_file(const std::string filename) {
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        continue;
    }
    return 0;
}

int run_on_input(std::string filename) {
    auto out = read_file(filename);
    
    return 0;
}

int main() {
    std::string testInputFile = "test_inputs.txt";
    std::string inputFile = "inputs.txt";
    int expectedTestOutput = 1;

    int testOutput = run_on_input(testInputFile);
    if (testOutput == expectedTestOutput) {
        int output = run_on_input(inputFile);
        std::cout << "Test ran succesfully\n";
        std::cout << std::format("Output is {}\n", output); 
    } else {
        std::cout << std::format("Test output should be {} but is {}\n", expectedTestOutput, testOutput);
    }
    return 0;
}
