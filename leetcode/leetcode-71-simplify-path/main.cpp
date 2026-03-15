#include <iostream>
#include <string>
#include <vector>

class Solution
{
public:
    std::string simplifyPath(std::string path)
    {
        if (path.empty() || path.front() != '/')
            return "/";

        std::vector<std::string> s;
        // Start with the root slash
        s.push_back("/");

        size_t i = 1;
        while (i < path.size())
        {
            if (path[i] == '/')
            {
                // Skip redundant slashes
                while (i < path.size() && path[i] == '/')
                {
                    i++;
                }
                // Only add a separator if the last element isn't already a slash
                if (!s.empty() && s.back() != "/")
                {
                    s.push_back("/");
                }
            }
            else if (path[i] == '.')
            {
                size_t j = i;
                while (j < path.size() && path[j] == '.')
                {
                    j++;
                }
                size_t count = j - i;

                // Check if this is a real '.' or '..' (must be followed by '/' or end of string)
                if ((j == path.size() || path[j] == '/') && count <= 2)
                {
                    if (count == 2)
                    { // ".." case
                        if (s.size() > 1)
                        {
                            s.pop_back(); // Remove the trailing "/"
                            s.pop_back(); // Remove the directory name
                        }
                    }
                    // count == 1 is "." (do nothing)
                    i = j;
                }
                else
                {
                    // It's a file name like "..." or "..hidden"
                    std::string name;
                    while (j < path.size() && path[j] != '/')
                    {
                        j++;
                    }
                    s.push_back(path.substr(i, j - i));
                    i = j;
                }
            }
            else
            {
                // Regular directory name
                size_t j = i;
                while (j < path.size() && path[j] != '/')
                {
                    j++;
                }
                s.push_back(path.substr(i, j - i));
                i = j;
            }
        }

        // Clean up: remove trailing slash if we aren't at root
        if (s.size() > 1 && s.back() == "/")
        {
            s.pop_back();
        }

        std::string result;
        for (const auto& e : s)
        {
            result += e;
        }

        return result.empty() ? "/" : result;
    }
};

int main(int argc, char** argv) { std::cout << Solution{}.simplifyPath("/../") << std::endl; }
