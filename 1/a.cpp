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

    std::sort(leftColumn.begin(), leftColumn.end());
    std::sort(rightColumn.begin(), rightColumn.end());

    int deltaSum = 0;
    for (int i = 0; i < leftColumn.size(); i++)
        deltaSum += std::abs(leftColumn[i] - rightColumn[i]);
    return deltaSum;
}

int main() {
    std::string testInputFile = "test_inputs.csv";
    std::string inputFile = "inputs.csv";
    int expectedTestOutput = 11;

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
