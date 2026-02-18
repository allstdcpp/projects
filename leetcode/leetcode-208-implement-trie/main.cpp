#include <iostream>
#include <string>

class Trie
{
public:
    struct Node
    {
        Node* list[256]{};
        bool word{};
    };
    Trie()
        : root_{new Node{}}
    {}
    void insert(std::string const& word)
    {
        if (word.empty())
            return;
        root_ = insert(word, 0, root_);
    }
    bool search(std::string const& word) { return search(word, 0, root_); }
    bool startsWith(std::string const& prefix) { return startsWith(prefix, 0, root_); }
private:

    Node* insert(std::string const& s, int index, Node* n)
    {
        if (!n)
            n = new Node{};
        if (index == s.size())
        {
            n->word = true;
            return n;
        }
        auto ch = s[index];
        n->list[ch] = insert(s, index + 1, n->list[ch]);
        return n;
    }

    bool search(std::string const& s, int index, Node* n)
    {
        if (!n)
            return false;
        if (index == s.size())
            return n->word;
        return search(s, index + 1, n->list[s[index]]);
    }

    bool startsWith(std::string const& prefix, int index, Node* n)
    {
        if (!n)
            return false;

        if (index < prefix.size())
        {
            auto ch = prefix[index];
            return startsWith(prefix, index + 1, n->list[ch]);
        }
        else
        {
            if (n->word)
                return true;

            for (auto e : n->list)
            {
                auto result = startsWith(prefix, index + 1, e);
                if (result)
                    return true;
            }

            return false;
        }
    }

    Node* root_;
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

int main(int argc, char** argv)
{
    std::string word{"Hello"};
    Trie* obj = new Trie();
    obj->insert(word);
    bool param_2 = obj->search(word);
    bool param_3 = obj->startsWith("He");
    return 0;
}
