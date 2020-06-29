#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <cassert>

using std::cin;
using std::cout;
using std::vector;
using std::max;

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

    bool Empty() const {
        return stack.empty();
    }

    int Top() const {
        assert(stack.size());
        return stack.back();
    }
};

class Queue {
private:
    StackWithMax in;
    StackWithMax out;
    void Adjust() {
        if(out.Empty()) {
            while (!in.Empty()) {
                out.Push(in.Top());
                in.Pop();
            }
        }
    }
public:
    void Push(int value) {
        in.Push(value);
    }
    void Pop() {
        Adjust();
        out.Pop();
    }
    int Top() {
        Adjust();
        return out.Top();
    }
    int Max() {
        return std::max(
            (in.Empty()) ? 0 : in.Max(), 
            (out.Empty()) ? 0 : out.Max()
        );
    }
};

void max_sliding_window_queue(vector<int> const & A, int w) {
    if(A.size() == static_cast<size_t>(w)) {
        std::cout << *std::max_element(A.begin(),A.end());
        return;
    }
    Queue window;
    for(size_t i = 0; i < w; i++) {
        window.Push(A[i]);
    }
    std::cout << window.Max() << ' ';
    for(size_t i = w; i < A.size(); i++) {
        window.Pop();
        window.Push(A[i]);
        std::cout << window.Max() << ' ';
    }
}

void max_sliding_window_deque(vector<int> const & A, int w) {
    if(A.size() == static_cast<size_t>(w)) {
        std::cout << *std::max_element(A.begin(),A.end());
        return;
    }
    std::deque<int> window;
    for(size_t i = 0; i < w; i++) {
        while(!window.empty() && A[window.back()] < A[i]) {
            window.pop_back();
        }
        window.push_back(i);
    }

    std::cout << A[window.front()] << ' ';

    std::pair<size_t,size_t> current_window{0,w-1};
    auto f_in_current_window = [&current_window](size_t i) {
        return current_window.first <= i && current_window.second >= i;
    }; 
    auto f_current_window_inc = [&current_window] {
        current_window.first++;
        current_window.second++;
    };

    // O(A.size())
    for(size_t i = w; i < A.size(); i++) {
#ifdef DEBUG
        std:: cerr << std::endl;
        for(auto i : window) {
            std::cerr << A[i] << ' ';
        }
        std:: cerr << std::endl;
#endif
        f_current_window_inc();
        if(!f_in_current_window(window.front())) {
            window.pop_front();
        }
        // Collapse all the previous elements until they are less than the pushed one
        while(!window.empty() && A[window.back()] < A[i]) {
            window.pop_back();
        }
        window.push_back(i);
        // That way we have the invariant of having max value for window in the front
        std::cout << A[window.front()] << ' ';
    }
}

int main() {
    int n = 0;
    cin >> n;

    vector<int> A(n);
    for (size_t i = 0; i < n; ++i)
        cin >> A.at(i);

    int w = 0;
    cin >> w;

    max_sliding_window_deque(A, w);

    return 0;
}
