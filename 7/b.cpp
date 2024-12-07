#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <format>
#include <vector>
#include <cmath>

long int apply_operator(long int a, long int b, const char op) {
    if (op == '*') {
        return a * b;
    } else if (op == '+') {
        return a + b;
    } else if (op == '|') { 
        return std::stol(std::to_string(a) + std::to_string(b));
    } else {
        std::invalid_argument( "Operator should be '*', '+' or '|'" );
    }
}

long int apply_operators(std::vector<int> arguments, std::string ops) {
    if (arguments.size() != ops.size() + 1) {
        throw std::invalid_argument( "Lengths of arguments and operators are not compatible" );
    }
    long int result = arguments[0];
    for (int i = 0; i < ops.size(); i++)
    {
        result = apply_operator(result, arguments[i+1], ops[i]);
    }
    return result;
}

std::vector<std::string> get_potential_operators(int n) {
    std::vector<std::string> operatorsCombinations;
    std::vector<std::string> deeperOperatorsCombinations = {""};

    std::vector<std::string> choices = {"*", "+", "|"};
    if (n > 1) {
        deeperOperatorsCombinations  = get_potential_operators(n - 1);
    }
    for (auto opComb : deeperOperatorsCombinations) {
        for (auto choice : choices) {
            std::string newOpComb = opComb + choice;
            operatorsCombinations.push_back(newOpComb);
        }
    }
    return operatorsCombinations;
}

struct Equation {
    long int result;
    std::vector<int> arguments;

    Equation(long int resultIn, std::vector<int> argumentsIn) {
        result = resultIn;
        arguments = argumentsIn;
    }

    void print() {
        std::cout << result << ": ";
        for (auto val : arguments) {
            std::cout << val  << " ";
        }
        std::cout << "\n";
    }
};

std::vector<Equation> read_file(const std::string filename) {
    std::ifstream file(filename);
    std::string line;

    std::string val;

    std::vector<Equation> equations;
    long int result;
    std::vector<int> arguments;
    while (std::getline(file, line)) {
        for (auto c : line) {
            if (c == ':')
            {
                result = std::stol(val);
                val = "";
                continue;
            }
            if (c ==  ' ')
            {
                if (!val.empty()) {
                    arguments.push_back(std::stol(val));
                    val = "";
                }
                continue;
            }
            val += c;
        }
        arguments.push_back(std::stol(val));
        val = "";

        equations.push_back(Equation(result, arguments));
        arguments.clear();
    }
    return equations;
}

long int run_on_input(std::string filename) {
    auto equations = read_file(filename);
    long int testResult;
    long int sumOfValids = 0;

    for (auto equation : equations) {
        std::vector<std::string> potentialOperators = get_potential_operators(equation.arguments.size() - 1);
        for (auto operators : potentialOperators) {
            testResult = apply_operators(equation.arguments, operators);
            if (testResult == equation.result) {
                sumOfValids += equation.result;
                break;
            }
        }
    }

    return sumOfValids;
}

int main() {
    std::string testInputFile = "test_inputs.txt";
    std::string inputFile = "inputs.txt";
    long int expectedTestOutput = 11387;

    long int testOutput = run_on_input(testInputFile);
    if (testOutput == expectedTestOutput) {
        long int output = run_on_input(inputFile);
        std::cout << "Test ran succesfully\n";
        std::cout << std::format("Output is {}\n", output); 
    } else {
        std::cout << std::format("Test output should be {} but is {}\n", expectedTestOutput, testOutput);
    }
    return 0;
}
