#include <cassert>
#include <concepts>
#include <iostream>

#include <boost/optional.hpp>

namespace ds {

template <typename T>
requires std::regular<T>
class binary_search_tree
{
public:
    struct node
    {
        T value;
        node* left{};
        node* right{};
    };
    using value_type = T;
    using node_type = node;
    using pointer = value_type*;
    using const_pointer = value_type const*;
    using reference = value_type&;
    using const_reference = value_type const&;

    template <typename U>
    requires std::constructible_from<T, U>
    void insert(U&& value)
    {
        root_ = insert(root_, std::forward<U>(value));
    }

    bool exists(T const& v)
    {
        auto current = root_;

        while (current)
        {
            if (current->value == v)
                return true;
            else if (v < current->value)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }

        return false;
    }

    boost::optional<value_type&> minimum()
    {
        boost::optional<value_type&> result;
        auto current = root_;

        while (current)
        {
            if (!current->left)
            {
                result.emplace(current->value);
                break;
            }
            current = current->left;
        }
        return result;
    }
    boost::optional<T&> maximum()
    {
        boost::optional<value_type&> result;
        auto current = root_;

        while (current)
        {
            if (!current->right)
            {
                result.emplace(current->value);
                break;
            }
            current = current->right;
        }
        return result;
    }
    void erase(T const& value) { root_ = erase(root_, value); }

    void clear()
    {
        clear(root_);
        root_ = nullptr;
    }

    template <typename F>
    requires std::invocable<F, const_reference>
    void process_inorder(F f)
    {
        process_inorder(root_, f);
    }

    template <typename F>
    requires std::invocable<F, const_reference>
    void process_preorder(F f)
    {
        process_preorder(root_, f);
    }

    template <typename F>
    requires std::invocable<F, const_reference>
    void process_postorder(F f)
    {
        process_postorder(root_, f);
    }

    ~binary_search_tree() { clear(); }

private:

    template <typename F>
    requires std::invocable<F, const_reference>
    void process_inorder(node_type const* n, F f)
    {
        if (!n)
            return;

        process_inorder(n->left, f);
        f(n->value);
        process_inorder(n->right, f);
    }

    template <typename F>
    requires std::invocable<F, const_reference>
    void process_preorder(node_type const* n, F f)
    {
        if (!n)
            return;

        f(n->value);
        process_inorder(n->left, f);
        process_inorder(n->right, f);
    }

    template <typename F>
    requires std::invocable<F, const_reference>
    void process_postorder(node_type const* n, F f)
    {
        if (!n)
            return;

        process_inorder(n->left, f);
        process_inorder(n->right, f);
        f(n->value);
    }

    void clear(node_type* parent)
    {
        if (!parent)
            return;

        clear(parent->left);
        clear(parent->right);

        delete parent;
    }

    template <typename U>
    node_type* insert(node_type* root, U&& value)
    {
        if (!root)
        {
            auto result = new node_type{std::forward<U>(value), nullptr, nullptr};
            ++size_;
            return result;
        }
        else if (value < root->value)
        {
            root->left = insert(root->left, std::forward<U>(value));
        }
        else if (value > root->value)
        {
            root->right = insert(root->right, std::forward<U>(value));
        }
        return root;
    }

    node_type* erase(node_type* root, T const& value)
    {
        if (!root)
        {
            return root;
        }
        else if (value < root->value)
        {
            root->left = erase(root->left, value);
        }
        else if (value > root->value)
        {
            root->right = erase(root->right, value);
        }
        else
        {
            // if no children delete and return nullptr
            if (!root->left && !root->right)
            {
                delete root;
                return nullptr;
            }
            else if (root->left && !root->right)
            {
                auto result = root->left;
                delete root;
                return result;
            }
            else if (root->right && !root->left)
            {
                auto result = root->right;
                delete root;
                return result;
            }
            else
            {
                node_type* min = root->right;
                while (true)
                {
                    if (min->left)
                        min = min->left;
                    else
                        break;
                }
                root->value = min->value;
                erase(root->right, min->value);
                return root;
            }
        }

        return root;
    }

    node_type* root_{};
    node_type* size_{};
};
} // namespace ds

int main(int argc, char** argv)
{
    ds::binary_search_tree<int> t;
    t.insert(100);
    t.insert(150);
    t.insert(50);
    t.insert(25);
    t.insert(75);
    t.insert(175);
    t.insert(125);

    t.process_inorder([](int const& v) { std::cout << v << " "; });
    std::cout << std::endl;

    {
        auto min = t.minimum();
        auto max = t.maximum();

        std::cout << "minimum: " << *min << ", maximum: " << *max << std::endl;

        t.erase(*min);
        t.erase(*max);
        t.process_inorder([](int const& v) { std::cout << v << " "; });
        std::cout << std::endl;
    }

    {
        auto min = t.minimum();
        auto max = t.maximum();
        std::cout << "minimum: " << *min << ", maximum: " << *max << std::endl;
    }

    {
        t.erase(100);
        t.process_inorder([](int const& v) { std::cout << v << " "; });
        std::cout << std::endl;
    }

    return 0;
}
