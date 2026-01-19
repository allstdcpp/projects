#include <cctype>
#include <stack>
#include <string>

class Solution
{
public:

    std::string decodeString(std::string s)
    {
        std::stack<int> multiplers;
        std::stack<std::string> letters;

        int i = 0;

        while (i != s.size())
        {
            if (std::isdigit(s[i]))
            {
                auto v = 0;

                auto j = i;
                while (j != s.size())
                {
                    auto n = s[i] - '0';
                    v = v * 10 + n;
                }

                multiplers.push(v);
                i = j;
            }
            else if (s[i] == '[')
            {
                continue;
            }
            else if (s[i] == ']')
            {
                auto digit = multiplers.top();
                multiplers.pop();

                auto str = letters.top();

                std::string temp;
                temp.reserve(str.size() * digit);

                for (auto i = 0; i < digit; ++i)
                {
                    temp.append(str);
                }

                letters.pop();
                letters.push(temp);
            }
            else if (std::isalnum(s[i]))
            {
                auto j = i;
                std::string t;
                while (std::isalnum(s[j]))
                {
                    t.push_back(s[j]);
                }
                letters.push(t);
                i = j;
            }
        }

        std::string result;

        while (!letters.empty())
        {
            result.append(letters.top());
            letters.pop();
        }

        return result;
    }
};

int main(int argc, char** argv) { return 0; }
