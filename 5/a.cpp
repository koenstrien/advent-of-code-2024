#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <format>
#include <vector>
#include <map>
#include <algorithm>

bool task_is_valid(std::vector<int> task, std::map<int, std::vector<int>> rules) {
    int page;
    int pageToCheck;
    std::vector<int> pageRules;

    for (int iPage = 0; iPage < task.size(); iPage++) {
        page = task[iPage];
        pageRules = rules[page];

        for (int jPage = iPage + 1; jPage < task.size(); jPage++) {
            pageToCheck = task[jPage];
            if (std::find(pageRules.begin(), pageRules.end(), pageToCheck) != pageRules.end()) {
                return false;
            }
        }
    }

    return true;
}

std::tuple<std::map<int, std::vector<int>>, std::vector<std::vector<int>>> read_file(const std::string filename) {
    std::ifstream file(filename);
    std::string line;
    std::map<int, std::vector<int>> printRules;
    std::vector<std::vector<int>> printTasks;
    std::vector<int> printRule;
    int key;
    int value;

    while (std::getline(file, line)) {
        if (line.empty()) {
            break;
        }
        value = std::stoi(line.substr(0, 2));
        key = std::stoi(line.substr(3, 2));
        printRules[key].push_back(value);
    }

    std::string valueStr;
    std::vector<int> printTask;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        while (std::getline(ss, valueStr, ',')) {
            value = std::stoi(valueStr);
            printTask.push_back(value);
        }
        printTasks.push_back(printTask);
        printTask.clear();
    }

    return std::make_tuple(printRules, printTasks);
}

int run_on_input(std::string filename) {
    auto [printRules, printTasks] = read_file(filename);
    bool valid;

    int result = 0;
    for (auto printTask : printTasks) {
        if (task_is_valid(printTask, printRules)) {
            result += printTask[printTask.size()/2];
        }
    }
    
    return result;
}

int main() {
    std::string testInputFile = "test_inputs.txt";
    std::string inputFile = "inputs.txt";
    int expectedTestOutput = 143;

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
