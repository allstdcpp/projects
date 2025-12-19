#include <iostream>
#include <list>
#include <unordered_map>

class LRUCache
{
public:
    explicit LRUCache(int capacity)
        : capacity_(capacity)
    {}
    int get(int key)
    {
        auto it = map_.find(key);
        if (it == std::end(map_))
            return -1;
        elements_.splice(elements_.begin(), elements_, it->second);
        return it->second->second;
    }
    void put(int key, int value)
    {
        auto [it, succ] = map_.try_emplace(key);
        if (succ)
        {
            elements_.emplace_front(key, value);
            it->second = elements_.begin();
        }
        else
        {
            it->second->second = value;
            elements_.splice(elements_.begin(), elements_, it->second);
        }
        erase_lru();
    }
private:

    void erase_lru()
    {
        if (elements_.size() <= capacity_)
            return;
        auto it = elements_.rbegin();
        auto key = it->first;

        map_.erase(key);
        elements_.pop_back();
    }

    int capacity_;
    std::list<std::pair<int, int>> elements_;
    std::unordered_map<int, typename std::list<std::pair<int, int>>::iterator> map_;
};

int main(int argc, char** argv)
{
    LRUCache c{2};

    c.put(1, 1);
    c.put(2, 2);

    std::cout << "get 1: " << c.get(1) << std::endl;
    c.put(3, 3);
    std::cout << "get 2: " << c.get(2) << std::endl;
}
