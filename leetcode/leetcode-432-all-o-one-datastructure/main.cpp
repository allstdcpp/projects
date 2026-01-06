#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>

class AllOne
{
    struct node
    {
        int count{};
        std::unordered_set<std::string> keys;
    };
public:
    AllOne() = default;
    void inc(std::string const& key)
    {
        auto [it, succ] = lookup_.try_emplace(key);
        if (succ)
        {
            auto stats_iterator = stats_.begin();
            if (stats_iterator == stats_.end() || stats_iterator->count != 1)
            {
                stats_.push_front({.count = 1, .keys = {key}});
            }
            else
            {
                stats_iterator->keys.insert(key);
            }
            it->second = stats_.begin();
        }
        else
        {
            auto stats_iterator = it->second;

            auto next = stats_iterator;
            next = std::next(next);

            if (next == stats_.end())
            {
                stats_.push_back({.count = stats_iterator->count + 1, .keys = {key}});
                it->second = std::prev(stats_.end());
            }
            else if (next->count != stats_iterator->count + 1)
            {
                it->second = stats_.insert(next, {.count = stats_iterator->count + 1, .keys = {key}});
            }
            else
            {
                next->keys.insert(key);
                it->second = next;
            }

            stats_iterator->keys.erase(key);
            if (stats_iterator->keys.empty())
            {
                stats_.erase(stats_iterator);
            }
        }
    }
    void dec(std::string const& key)
    {
        auto it = lookup_.find(key);
        auto list_iterator = it->second;

        if (list_iterator->count != 1)
        {
            auto prev = list_iterator;

            if (list_iterator != stats_.begin())
            {
                prev = std::prev(prev);
            }

            if (prev->count != (list_iterator->count - 1))
            {
                it->second = stats_.insert(list_iterator, {.count = list_iterator->count - 1, .keys = {key}});
            }
            else
            {
                prev->keys.insert(key);
                it->second = prev;
            }
        }

        list_iterator->keys.erase(key);

        if (list_iterator->count == 1)
        {
            lookup_.erase(it);
        }

        if (list_iterator->keys.empty())
        {
            stats_.erase(list_iterator);
        }
    }
    std::string getMaxKey()
    {
        std::string result;
        auto it = stats_.rbegin();

        if (it != stats_.rend())
        {
            result = *it->keys.begin();
        }

        return result;
    }
    std::string getMinKey()
    {
        std::string result;
        auto it = stats_.begin();

        if (it != stats_.end())
        {
            result = *it->keys.begin();
        }

        return result;
    }
private:
    std::list<node> stats_;
    std::unordered_map<std::string, std::list<node>::iterator> lookup_;
};

int main(int argc, char** argv)
{
    AllOne a;
    a.inc("hello");
    a.inc("hello");
    std::cout << a.getMaxKey() << std::endl;
    std::cout << a.getMinKey() << std::endl;
    a.dec("hello");
    a.dec("hello");
    std::cout << a.getMaxKey() << std::endl;
    a.inc("hello");
    std::cout << a.getMinKey() << std::endl;
}
