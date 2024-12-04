#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <sstream>
#include <format>
#include <tuple>
#include <vector>

typedef std::vector<std::vector<char>> Puzzle;

bool in_bounds(std::tuple<int, int> loc, Puzzle puzzle) {
    auto [i, j] = loc;
    return (i >= 0) && (i < puzzle.size()) && (j >= 0) && (j < puzzle[0].size());
}

std::string get_word_in_direction(Puzzle puzzle, std::tuple<int, int> loc, std::tuple<int, int> direction, int nLetters = 4) {
    int i;
    int j;
    auto [iStart, jStart] = loc;
    auto [iDir, jDir] = direction;
    std::string word = "";

    for (int iLetter = 0; iLetter < nLetters; iLetter++) {
        i = iStart + iLetter * iDir;
        j = jStart + iLetter * jDir;
        if (!in_bounds(std::make_tuple(i, j), puzzle)) {
            break;
        }
        word += puzzle[i][j];
    }

    return word;
}

void print_puzzle(Puzzle puzzle){
    for (int i = 0; i < puzzle.size(); i++) {
        for (int j = 0; j < puzzle[0].size(); j++) {
            std::cout << puzzle[i][j];
        }
        std::cout << "\n";
    }
}


Puzzle read_file(const std::string filename) {
    std::ifstream file(filename);
    std::string line;
    Puzzle puzzle;
    std::vector<char> puzzleRow;

    while (std::getline(file, line)) {
        for (char& letter : line) {
            puzzleRow.push_back(letter);
        }
        puzzle.push_back(puzzleRow);
        puzzleRow.clear();
    }
    return puzzle;
}

int count_matches_in_all_directions(Puzzle puzzle, std::tuple<int, int> loc, std::string matchWord = "XMAS") {
    std::vector<int> iDirs = {-1, 0, 1};
    std::vector<int> jDirs = {-1, 0, 1};
    int nMatches = 0;
    for (auto iDir : iDirs) {
        for (auto jDir : jDirs) {
            if (iDir == 0 && jDir == 0) {
                continue;
            }
            std::string word = get_word_in_direction(puzzle, loc, std::make_tuple(iDir, jDir));
            if (word == matchWord) {
                nMatches += 1;
            }
        }
    }
    return nMatches;
}

int run_on_input(std::string filename) {
    auto puzzle = read_file(filename);
    int nRows = puzzle.size();
    int nCols = puzzle[0].size();

    int nMatchesTotal = 0;
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            if (puzzle[i][j] == 'X') {
                int nMatches = count_matches_in_all_directions(puzzle, std::make_tuple(i, j));
                nMatchesTotal += nMatches;
            }
        }
    }

    return nMatchesTotal;
}

int main() {
    std::string testInputFile = "test_inputs.txt";
    std::string inputFile = "inputs.txt";
    int expectedTestOutput = 18;

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
