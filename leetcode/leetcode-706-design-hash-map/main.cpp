#include <cctype>
#include <functional>
#include <string>
#include <vector>

class MyHashMap
{
public:
    static constexpr auto max = 1000001;
    MyHashMap()
        : v_(max, -1)
    {}

    void put(int key, int value)
    {
        if (key < max)
            v_[key] = value;
    }

    void remove(int key)
    {
        if (key < max)
            v_[key] = -1;
    }

    int get(int key)
    {
        if (key >= max)
            return -1;
        return v_[key];
    }

    std::vector<int> v_;
};

int main(int argc, char** argv) { return 0; }
