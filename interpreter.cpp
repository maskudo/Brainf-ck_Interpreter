#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " Program" << std::endl;
        exit(1);
    }
    std::string program = argv[1];
    std::vector<unsigned char> tape = {0};
    int cell_index = 0;
    unsigned char user_input;
    std::stack<int> loop_stack;
    std::unordered_map<int, int> bracket_index_dict;

    for (int ip = 0; ip < program.size(); ip++) {
        if (program[ip] == '[') {
            loop_stack.push(ip);
        } else if (program[ip] == ']') {
            if (loop_stack.empty()) {
                std::cerr << "No matching '[' for ']' at index " << ip << std::endl;
                exit(1);
            }
            auto poppedEle = loop_stack.top();
            bracket_index_dict[ip] = poppedEle;
            bracket_index_dict[poppedEle] = ip;
            loop_stack.pop();
        }
    }
    if (!loop_stack.empty()) {
        std::cerr << "No ending ']' for '[' at index " << loop_stack.top() << std::endl;
        exit(1);
    }
    for (int ip = 0; ip < program.size(); ip++) {
        switch (program[ip]) {
        case '+': {
            tape[cell_index] += 1;
            break;
        }
        case '-': {
            tape[cell_index] -= 1;
            break;
        }
        case '>': {
            cell_index++;
            if (cell_index == tape.size()) {
                tape.push_back(0);
            }
            break;
        }
        case '<': {
            cell_index--;
            break;
        }
        case '[': {
            if (tape[cell_index] == 0) {
                ip = bracket_index_dict[ip];
            }
            break;
        }
        case ']': {
            if (tape[cell_index] != 0) {
                ip = bracket_index_dict[ip];
            }
            break;
        }
        case '.': {
            std::cout << tape[cell_index];
            break;
        }
        case ',': {
            user_input = std::cin.get();
            tape[cell_index] = user_input;
            break;
        }
        default: {
            break;
        }
        }
    }
    return 0;
}