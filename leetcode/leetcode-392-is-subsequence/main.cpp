#include <iostream>
#include <string>

class Solution
{
public:
    bool isSubsequence(std::string const& a, std::string const& b)
    {
        size_t i = 0;
        size_t j = 0;

        while(i < a.size()) {

            while(j < b.size()) {
                if(a[i] == b[j++]) {
                    ++i;
                    break;
                }
            }

            if(j == b.size()) break;

        }

        return i == a.size();
    }
    
};

int main(int argc, char** argv)
{
    return Solution{}.isSubsequence("axc","ahhgdc");
}
