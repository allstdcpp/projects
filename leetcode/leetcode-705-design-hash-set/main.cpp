#include <cctype>
#include <functional>
#include <string>
#include <vector>

class MyHashSet
{
public:
    static constexpr auto max = 1000001;
    MyHashSet()
        : v_(max, -1)
    {}

    void add(int key)
    {
        if (key < max)
            v_[key] = key;
    }

    void remove(int key)
    {
        if (key < max)
            v_[key] = -1;
    }

    bool contains(int key)
    {
        if (key >= max)
            return false;
        return v_[key] != -1;
    }

    std::vector<int> v_;
};

int main(int argc, char** argv) { return 0; }
