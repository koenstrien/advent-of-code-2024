#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <tuple>
#include <vector>
#include <format>

std::vector<std::vector<int>> read_file(std::string filename) {
    std::vector<int> row;
    std::vector<std::vector<int>> rows;

    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        int value;
        std::istringstream lineStream(line);
        while (lineStream >> value) {
            row.push_back(value);
        }
        rows.push_back(row);
        row.clear();
    }

    file.close();

    return rows;
}

bool is_safe(std::vector<int> row) {
    if (row[1] - row[0] == 0) {
        return false;
    }
    int direction = std::abs(row[1] - row[0]) / (row[1] - row[0]);

    int previous_value = row[0];
    for (int i = 1; i < row.size(); i++) {
        int delta = row[i] - row[i-1];
        if (delta * direction < 1 || delta * direction > 3) {
            return false;
        }
    }
    return true;
}

int run_on_input(std::string filename) {
    auto rows = read_file(filename);

    int nSafe = 0;
    for (auto row : rows) {
        if (is_safe(row)) {
            nSafe += 1;
        }
    }
    return nSafe;
}

int main() {
    std::string testInputFile = "result.csv";
    std::string inputFile = "inputs.csv";
    int expectedTestOutput = 2;

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
