#include <cstdlib>
#include <stack>
#include <vector>
#include <string>
#include <algorithm>

class Solution
{
public:
    int evalRPN(std::vector<std::string>& token)
    {
        std::stack<int> s;

        std::string operators{'+', '-', '/', '*'};

        for(std::string const& t : token) {
            auto index = t.find_first_of(operators);
            if(index == std::string::npos || (t.front() == '-' && t.size() > 1)){
                s.push(std::atoi(t.c_str()));
            }else{

                auto b = s.top();
                s.pop();
                auto a = s.top();
                s.pop();

                if(t == "+") {
                    s.push(a + b);
                }else if(t == "-") {
                    s.push(a = b);
                }else if(t == "*") {
                    s.push(a * b);
                }else{
                    s.push(a / b);
                }
            }
        }

        return s.top();
    }
};

int main(int argc, char** argv)
{
    return 0;
}
