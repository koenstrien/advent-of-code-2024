#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <sstream>
#include <format>
#include <vector>

std::string read_file(const std::string filename) {
    std::ifstream file(filename);
    std::string line;
    std::string text;

    while (std::getline(file, line)) {
        text += line;
    }
    return text;
}

int run_on_input(std::string filename) {
    auto text = read_file(filename);
    std::vector<std::string> matches;
    int result = 0;
    bool enabled = true;
    
    std::regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\)|do\(\)|don't\(\))");
    std::smatch match;
    std::string::const_iterator searchStart(text.cbegin());
    while (std::regex_search(searchStart, text.cend(), match, pattern)) {
        searchStart = match.suffix().first; // Move the iterator forward
        if (match[0] == "don't()") {
            enabled = false;
            continue;
        }
        if (match[0] == "do()") {
            enabled = true;
            continue;
        }
        if (enabled) {
            result += std::stoi(match[1]) * std::stoi(match[2]);
        }        
    }
    return result;
}

int main() {
    std::string testInputFile = "test_inputs_b.txt";
    std::string inputFile = "inputs.txt";
    int expectedTestOutput = 48;

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
