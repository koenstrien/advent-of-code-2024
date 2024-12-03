#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <ranges>
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

void print_row(std::vector<int> row) {
    for (auto value : row) {
        std::cout << value << " ";
    }
    std::cout << "\n";
}

int illegal_delta(std::vector<int> row) {
    if (row[1] - row[0] == 0) {
        return 0;
    }
    int direction = (row[1] - row[0]) / std::abs(row[1] - row[0]);

    for (int i = 0; i < row.size() - 1; i++) {
        int delta = row[i+1] - row[i];
        if (((delta * direction) < 1) || ((delta * direction) > 3)) {
            return i;
        }
    }
    return -1;
}

bool is_safe_with_removal(std::vector<int> row) {
    std::vector<int> rowCopy;
    std::vector<int> potentialRemoval;

    int i = illegal_delta(row);
    if (i == -1) {
        return true;
    } else {
        potentialRemoval.push_back(i);
        potentialRemoval.push_back(i + 1);
        if (i == 1) {
            potentialRemoval.push_back(0);
        }

        for (auto iRemove : potentialRemoval) {
            rowCopy = row;
            rowCopy.erase(rowCopy.begin() + iRemove);
            int j = illegal_delta(rowCopy);
            if (j == -1) {
                return true;
            }
        }
    }
    return false;
}

int run_on_input(std::string filename) {
    auto rows = read_file(filename);
    std::vector<int> rowCopy;
    int nSafe = 0;
    for (auto [i, row] : std::views::enumerate(rows)) {
        if (is_safe_with_removal(row)) {
            nSafe += 1;
            std::cout << i << "\n";
        }
    }
    return nSafe;
}

int main() {
    std::string testInputFile = "test_inputs.csv";
    std::string inputFile = "inputs.csv";
    int expectedTestOutput = 4;

    int testOutput = run_on_input(testInputFile);
    if (testOutput == expectedTestOutput) {
        std::cout << "Test ran succesfully\n";
        int output = run_on_input(inputFile);
        std::cout << std::format("Output is {}\n", output); 
    } else {
        std::cout << std::format("Test output should be {} but is {}\n", expectedTestOutput, testOutput);
    }
    return 0;
}
