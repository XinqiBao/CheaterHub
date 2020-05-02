#include "wordscapes.h"

#include <fstream>
#include <map>
#include <queue>
#include <string>

Dictionary::Node::Node() {}

Dictionary::Dictionary(const char* filename)
{
    header = new Node();
    std::ifstream dictfile(filename);
    std::string word;
    while (dictfile >> word)
    {
        Node* tmp = header;
        for (char ch : word)
        {
            if (tmp->next[ch - 'a'] == nullptr)
                tmp->next[ch - 'a'] = new Node();
            tmp = tmp->next[ch - 'a'];
        }
        tmp->isWord = true;
    }
    dictfile.close();
}

Dictionary::Node::~Node()
{
    for (int i = 0; i < 26; i++)
        if (next[i] != nullptr) delete next[i];
}

Dictionary::~Dictionary() { delete header; }

bool Dictionary::findWord(std::string& word)
{
    Node* tmp = header;
    for (char ch : word)
    {
        if (tmp->next[ch - 'a'] == nullptr) return false;
        tmp = tmp->next[ch - 'a'];
    }
    return tmp->isWord;
}

//TODO: get filename from config file
Wordscapes::Wordscapes() { dict = new Dictionary("myDictionary"); }

Wordscapes::~Wordscapes() {}

void Wordscapes::stripInput(std::string& given, std::string& search)
{
    for (auto i = given.begin(); i != given.end(); i++)
    {
        if (*i >= 'a' && *i <= 'z')
            continue;
        else if (*i >= 'A' && *i <= 'Z')
            *i += 'a' - 'A';
        else
            given.erase(i--);
    }
    for (auto i = search.begin(); i != search.end(); i++)
    {
        if ((*i >= 'a' && *i <= 'z') || *i == '*')
            continue;
        else if (*i >= 'A' && *i <= 'Z')
            *i += 'a' - 'A';
        else
            given.erase(i--);
    }
}

std::vector<std::string> Wordscapes::solve(std::string& given,
                                           std::string& search)
{
    // strip input string, remove unexpected characters
    stripInput(given, search);

    std::vector<std::string> result;
    std::map<char, int> mp;
    std::queue<std::pair<std::string, std::map<char, int>>> qu;

    for (char ch : given) mp[ch]++;
    for (char ch : search)
    {
        if (ch >= 'a' && ch <= 'z') mp[ch]--;
        if (mp[ch] < 0) return {};
    }
    qu.push({search, mp});

    while (!qu.empty())
    {
        std::string word = qu.front().first;
        auto wmp         = qu.front().second;
        qu.pop();
        std::size_t found = word.find('*');
        if (found == std::string::npos)
        {
            if (dict->findWord(word)) result.push_back(word);
        }
        else
        {
            for (auto& m : wmp)
            {
                if (m.second != 0)
                {
                    auto tmp_word = word;
                    auto tmp_wmp  = wmp;
                    tmp_word.replace(found, 1, 1, m.first);
                    tmp_wmp[m.first]--;
                    qu.push({tmp_word, tmp_wmp});
                }
            }
        }
    }
    return result;
}
