#include <boost/optional/optional.hpp>
#include <cassert>
#include <functional>
#include <iostream>
#include <list>
#include <tuple>
#include <unordered_map>
#include <utility>

#include <boost/optional.hpp>

namespace cache {
template <typename Key, typename Value, typename Hash = std::hash<Key>>
class lru_cache
{
    using key_storage_type = std::list<Key>;
    using lookup_storage_type = std::unordered_map<Key, std::pair<Value, typename key_storage_type::iterator>, Hash>;
public:
    using value_type = Value;
    using size_type = size_t;
    using reference = Value&;
    using const_reference = const Value&;
    using pointer = Value*;
    using const_pointer = const Value*;
    using return_type = boost::optional<Value&>;
    using const_return_type = boost::optional<const Value&>;

    explicit lru_cache(size_type capacity);
    lru_cache(lru_cache const&) = default;
    lru_cache& operator=(lru_cache const&) = default;
    lru_cache(lru_cache&&) = default;
    lru_cache& operator=(lru_cache&&) = default;

    template <typename K, typename V>
    void insert(K&& key, V&& value);

    const_return_type at(Key const& key) const;

    void erase(Key const& key);

    key_storage_type const& keys() const { return keys_; }
    size_type size() const { return lookup_.size(); }
    bool empty() const { return lookup_.size(); }

    ~lru_cache() = default;
private:

    void evict();

    size_type capacity_;
    lookup_storage_type lookup_;
    mutable key_storage_type keys_;
};

template <typename Key, typename Value, typename Hash>
lru_cache<Key, Value, Hash>::lru_cache(size_type capacity)
    : capacity_{capacity}
{
    lookup_.reserve(capacity_);
}

template <typename Key, typename Value, typename Hash>
lru_cache<Key, Value, Hash>::const_return_type lru_cache<Key, Value, Hash>::at(Key const& key) const
{
    const_return_type result;
    auto it = lookup_.find(key);

    if (it == lookup_.end())
        return result;

    result.emplace(it->second.first);

    keys_.splice(keys_.begin(), keys_, it->second.second);

    return result;
}

template <typename Key, typename Value, typename Hash>
template <typename K, typename V>
void lru_cache<Key, Value, Hash>::insert(K&& key, V&& value)
{
    auto it = lookup_.find(key);

    if (it == lookup_.end())
    {
        if (capacity_ == lookup_.size())
        {
            evict();
        }

        keys_.push_front(key);
        lookup_.emplace(
            std::piecewise_construct,
            std::forward_as_tuple(std::forward<K>(key)),
            std::forward_as_tuple(std::forward<V>(value), keys_.begin()));
    }
    else
    {
        it->second.first = std::forward<Value>(value);
    }
}

template <typename Key, typename Value, typename Hash>
void lru_cache<Key, Value, Hash>::evict()
{
    auto it = keys_.rbegin();

    lookup_.erase(*it);
    keys_.pop_back();
}

} // namespace cache

int main(int argc, char** argv)
{
    cache::lru_cache<int, int> c{2};

    return 0;
}
