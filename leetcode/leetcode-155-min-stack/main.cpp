#include <iostream>
#include <optional>
#include <vector>

class MinStack
{
public:
    MinStack() = default;

    void push(int val)
    {
        if (v.empty())
            v.emplace_back(val, val);
        else
            v.emplace_back(val, std::min(val, v.back().second));
    }

    void pop() { v.pop_back(); }

    int top() { return v.back().first; }

    int getMin() { return v.back().second; }
private:
    std::vector<std::pair<int, int>> v;
};

int main(int argc, char** argv) { return 0; }
