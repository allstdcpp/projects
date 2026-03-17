#include <iostream>
#include <string>
#include <string_view>

#include <boost/optional.hpp>
namespace ds {

template <typename V, size_t R>
class trie
{
public:
    trie()
        : root_{new node{}}
    {}
    struct node
    {
        V value;
        node* links[R] = {0};
    };

    void insert(std::string_view s, V&& v)
    {
        auto current = root_;

        for (auto e : s)
        {
            if (!current->links[(int)e])
            {
                current->links[(int)e] = new node{};
            }
            current = current->links[(int)e];
        }
        current->value = std::forward<V>(v);
    }

    boost::optional<V&> find(std::string_view s) { return find(s, 0, root_); }

    ~trie()
    {
        clear();
        delete root_;
    }

    void clear()
    {
        clear(root_);
        root_ = new node{};
    }

private:
    void clear(node* root)
    {
        if (!root)
            return;

        for (auto n : root->links)
        {
            if (n)
            {
                clear(n);
            }
        }

        delete root;
    }
    boost::optional<V&> find(std::string_view s, size_t index, node* n)
    {
        boost::optional<V&> result;

        if (!n)
            return result;

        if (index == s.size())
        {
            result = n->value;
            return result;
        }

        return find(s, index + 1, n->links[(int)s[index]]);
    }
    node* root_;
};
} // namespace ds

int main()
{
    ds::trie<int, 256> s;
    s.insert("Hello", 5);
    s.insert("Hello World", 6);
    s.insert("Hell", 7);
    s.insert("She", 8);
    s.insert("Shell", 9);

    auto a = s.find("Hello");
    if (a)
        std::cout << "Hello: " << *a << std::endl;

    auto b = s.find("Shell");
    if (b)
        std::cout << "Shell: " << *b << std::endl;

    auto c = s.find("Shells");
    if (!c)
        std::cout << "Shells: Not found." << std::endl;
    return 0;
}
