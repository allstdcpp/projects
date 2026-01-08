#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

class Solution
{
public:
    std::vector<int> findSubstring(std::string s, std::vector<std::string>& words)
    {
        std::vector<int> result;
        std::string current;

        auto size =
            std::accumulate(words.begin(), words.end(), 0z, [](auto const& v, auto const& e) { return e.size() + v; });

        std::sort(words.begin(), words.end());

        std::vector<bool> visited(words.size(), false);

        std::function<void(int)> f = [&](int start) {
            if (current.size() == size)
            {
                result.push_back(start);
                return;
            }

            for (auto i = 0; i < words.size(); ++i)
            {
                if (visited[i] || (i > 0 && words[i] == words[i - 1] && !visited[i - 1]))
                    continue;

                visited[i] = true;

                current.append(words[i]);
                auto index = s.find(current);

                if (index != std::string::npos)
                {
                    f(index);
                }

                current.erase(current.size() - words[i].size());
                visited[i] = false;
            }
        };

        f(0);

        return result;
    }
};

int main(int argc, char** argv) {}
