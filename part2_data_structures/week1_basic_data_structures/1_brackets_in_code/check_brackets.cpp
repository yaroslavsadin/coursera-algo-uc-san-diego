#include <iostream>
#include <stack>
#include <string>

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);

    std::stack <Bracket> opening_brackets_stack;
    int fail_pos = 0;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket, write your code here
            opening_brackets_stack.push(Bracket(next,position));
        }

        if (next == ')' || next == ']' || next == '}') {
            // Process closing bracket, write your code here
            if(opening_brackets_stack.empty()) {
                fail_pos = position + 1;
                break;
            }
            auto last_opening_bracket = opening_brackets_stack.top();
            if(last_opening_bracket.Matchc(next)) {
                opening_brackets_stack.pop();
            } else {
                fail_pos = position + 1;
                break;
            }
        }
    }

    // Printing answer, write your code here
    if(fail_pos) {
        std::cout << fail_pos << std::endl;
    } else if(opening_brackets_stack.empty()) {
        std::cout << "Success";
    } else {
        std::cout << opening_brackets_stack.top().position + 1 << std::endl;
    }

    return 0;
}
