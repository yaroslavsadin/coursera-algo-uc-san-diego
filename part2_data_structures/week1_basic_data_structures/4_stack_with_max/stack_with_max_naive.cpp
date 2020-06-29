#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

using std::cin;
using std::string;
using std::vector;
using std::cout;
using std::max_element;

class StackWithMax {
    vector<int> stack;
    vector<int> max_;

  public:

    void Push(int value) {
        if(max_.empty() || max_.back() <= value) {
            max_.push_back(value);
        }
        stack.push_back(value);
    }

    void Pop() {
        assert(stack.size());
        if(!max_.empty() && max_.back() == stack.back()) {
            max_.pop_back();
        }
        stack.pop_back();
    }

    int Max() const {
        assert(stack.size());
        return max_.back();
    }
};

int main() {
    int num_queries = 0;
    cin >> num_queries;

    string query;
    string value;

    StackWithMax stack;

    for (int i = 0; i < num_queries; ++i) {
        cin >> query;
        if (query == "push") {
            cin >> value;
            stack.Push(std::stoi(value));
        }
        else if (query == "pop") {
            stack.Pop();
        }
        else if (query == "max") {
            cout << stack.Max() << "\n";
        }
        else {
            assert(0);
        }
    }
    return 0;
}