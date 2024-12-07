#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <format>
#include <vector>
#include <unistd.h>

bool make_move(std::vector<std::vector<bool>> obstacleMap, std::tuple<int, int> *position, int *direction) {
    auto [newRow, newCol] = *position;
    
    if (*direction == 0) {
        newRow -= 1;
    } else if (*direction == 1) {
        newCol += 1;
    } else if (*direction == 2) {
        newRow += 1;
    } else if (*direction == 3) {
        newCol -= 1;
    }

    if (newRow < 0 || newRow >= obstacleMap.size() || newCol < 0 || newCol >= obstacleMap[0].size()) {
        return false;  // Out of map
    }

    if (obstacleMap[newRow][newCol]) {
        *direction = (*direction + 1) % 4;  // only rotate
    } else {
        // update position
        std::get<0>(*position) = newRow;
        std::get<1>(*position) = newCol;
    }

    return true;
}

std::tuple<std::vector<std::vector<bool>>, std::tuple<int, int>, int> read_file(const std::string filename) {
    std::ifstream file(filename);
    std::string line;

    std::vector<std::vector<bool>> obstacleMap;
    std::tuple<int, int> position;
    int direction = 0;
    
    std::vector<bool> obstacleRow;
    int iCol;
    int iRow = 0;
    while (std::getline(file, line)) {
        iCol = 0;
        for (auto c : line) {
            if (c == '#') {
                obstacleRow.push_back(true);
            } else {
                obstacleRow.push_back(false);
            }

            if (c == '^') {
                position = std::make_tuple(iRow, iCol);
            }
            iCol++;
        }
        obstacleMap.push_back(obstacleRow);
        obstacleRow.clear();
        iRow++;
    }

    return std::make_tuple(obstacleMap, position, direction);
}

int run_on_input(std::string filename) {
    auto [obstacleMap, position, direction] = read_file(filename);
    
    std::vector<std::vector<bool>> positionMap(obstacleMap);
    std::vector<std::vector<int>> directionMap;
    
    for (auto& row : positionMap) {
        for (auto val : row) {
            val = false;
        }
    }

    positionMap[std::get<0>(position)][std::get<1>(position)] = true;
    while (make_move(obstacleMap, &position, &direction)) {
        positionMap[std::get<0>(position)][std::get<1>(position)] = true;
    }

    int result = 0;
    for (auto row : positionMap) {
        for (auto val : row) {
            if (val) {
                result++;
            }
        }
    }

    return result;
}

int main() {
    std::string testInputFile = "test_inputs.txt";
    std::string inputFile = "inputs.txt";
    int expectedTestOutput = 41;

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
