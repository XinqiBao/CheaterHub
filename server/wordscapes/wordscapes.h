#pragma once
#include <fstream>
#include <string>
#include <vector>

class Dictionary
{
private:
    class Node
    {
    public:
        bool isWord    = false;
        Node* next[26] = {0};

        Node();
        ~Node();
    };
    Node* header;

public:
    Dictionary(const char* filename);
    ~Dictionary();

    bool findWord(std::string& word);
};

class Wordscapes
{
private:
    Dictionary* dict;

    void stripInput(std::string& given, std::string& search);

public:
    Wordscapes();
    ~Wordscapes();

    std::vector<std::string> solve(std::string& given, std::string& search);
};
