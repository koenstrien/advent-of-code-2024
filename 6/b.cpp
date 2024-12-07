#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <format>
#include <vector>
#include <unistd.h>
#include <cmath>

bool make_move(std::vector<std::vector<bool>> obstacleMap, std::tuple<int, int> *position, int *direction) {
    auto [newRow, newCol] = *position;
    
    if (*direction == 1) {
        newRow -= 1;
    } else if (*direction == 2) {
        newCol += 1;
    } else if (*direction == 3) {
        newRow += 1;
    } else if (*direction == 4) {
        newCol -= 1;
    }

    if (newRow < 0 || newRow >= obstacleMap.size() || newCol < 0 || newCol >= obstacleMap[0].size()) {
        return false;  // Out of map
    }

    if (obstacleMap[newRow][newCol]) {
        *direction = *direction % 4 + 1;  // only rotate
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
    int direction = 1;
    
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
    std::tuple<int, int> startingPosition(position);
    std::tuple<int, int> previousPosition(position);
    
    std::vector<std::vector<bool>> positionMap(obstacleMap);
    std::vector<std::vector<int>> directionMap;
    std::vector<int> directionRow;
    for (auto& row : positionMap) {
        for (auto val : row) {
            val = false;
            directionRow.push_back(0);
        }
        directionMap.push_back(directionRow);
        directionRow.clear();
    }

    std::vector<std::vector<std::vector<bool>>> potentialObstacleMaps;

    positionMap[std::get<0>(position)][std::get<1>(position)] = true;
    while (make_move(obstacleMap, &position, &direction)) {
        if (!positionMap[std::get<0>(position)][std::get<1>(position)]) {
            std::vector<std::vector<bool>> potentialObstacleMap(obstacleMap);
            potentialObstacleMap[std::get<0>(position)][std::get<1>(position)] = true;
            potentialObstacleMaps.push_back(potentialObstacleMap);
        }
        positionMap[std::get<0>(position)][std::get<1>(position)] = true;
    }

    int loopCounter = 0;
    int i = 0;
    for (std::vector<std::vector<bool>> potentialObstacleMap : potentialObstacleMaps) {
        i++;
        std::cout << "trying " << i << " of " << potentialObstacleMaps.size() << "\n";
        position = startingPosition;
        direction = 1;
        std::vector<std::vector<int>> directionMapCopy(directionMap);

        directionMapCopy[std::get<0>(position)][std::get<1>(position)] = direction;
        while (make_move(potentialObstacleMap, &position, &direction)) {
            if ((directionMapCopy[std::get<0>(position)][std::get<1>(position)] & (1 << direction)) > 0) {
                loopCounter++;
                break;
            }
            directionMapCopy[std::get<0>(position)][std::get<1>(position)] |= (1 << direction);
        }
    }

    return loopCounter;
}

int main() {
    std::string testInputFile = "test_inputs.txt";
    std::string inputFile = "inputs.txt";
    int expectedTestOutput = 6;

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
