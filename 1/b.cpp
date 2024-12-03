#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <tuple>
#include <vector>
#include <format>

std::tuple<std::vector<int>, std::vector<int>> read_file(std::string filename) {
    std::vector<int> leftColumn;
    std::vector<int> rightColumn;

    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        int value1;
        int value2;
        lineStream >> value1;
        lineStream >> value2;

        leftColumn.push_back(value1);
        rightColumn.push_back(value2);
    }

    file.close();

    return std::make_tuple(leftColumn, rightColumn);
}

int run_on_input(std::string filename) {
    auto [leftColumn, rightColumn] = read_file(filename);

    int score = 0;
    for (auto value : leftColumn) {
        int count = std::count(rightColumn.begin(), rightColumn.end(), value);
        score += count * value;
    }
    return score;
}

int main() {
    std::string testInputFile = "test_inputs.csv";
    std::string inputFile = "inputs.csv";
    int expectedTestOutput = 31;

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
