#include <iostream>
#include <string>

class WordDictionary
{
public:
    struct Node
    {
        Node* next[26]{0};
        bool end{};
    };
    WordDictionary()
        : root_{new Node{}}
    {}

    void addWord(std::string word) { root_ = addWord(word, 0, root_); }

    bool search(std::string word) { return search(word, 0, root_); }
private:

    Node* addWord(std::string const& s, int index, Node* n)
    {
        if (!n)
            n = new Node{};

        if (index == s.size())
        {
            n->end = true;
            return n;
        }

        n->next[s[index] - 'a'] = addWord(s, index + 1, n->next[s[index] - 'a']);

        return n;
    }

    bool search(std::string const& s, int index, Node* n)
    {
        if (!n)
            return false;

        if (index == s.size())
            return n->end;

        if (s[index] == '.')
        {
            for (auto e : n->next)
            {
                auto result = search(s, index + 1, e);
                if (result)
                    return true;
            }
            return false;
        }
        else
        {
            return search(s, index + 1, n->next[s[index] - 'a']);
        }
    }

    Node* root_;
};

int main(int argc, char** argv)
{
    WordDictionary wordDictionary;
    wordDictionary.addWord("bad");
    wordDictionary.addWord("dad");
    wordDictionary.addWord("mad");
    std::cout << wordDictionary.search("pad") << std::endl;
    std::cout << wordDictionary.search("bad") << std::endl;
    std::cout << wordDictionary.search(".ad") << std::endl;
    std::cout << wordDictionary.search("b..") << std::endl;
}
