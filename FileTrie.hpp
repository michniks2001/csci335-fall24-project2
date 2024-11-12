/**
 * @file FileTrie.hpp
 * @brief Defines the interface for the FileTrie class & implementation of the TrieNode struct
 */


#pragma once
#include <unordered_map>
#include <unordered_set>
#include <cctype>
#include <string>
#include <iostream>
#include <functional>
#include "File.hpp"

struct FileTrieNode {   
    char stored;

    std::unordered_set<File*> matching;
    std::unordered_map<char, FileTrieNode*> next;

    FileTrieNode(const char& c = ' ', File* to_add = nullptr) : stored{c}, matching{}, next{} {
        if (to_add) { matching.insert(to_add); }
    }
};

class FileTrie {
    private:
        FileTrieNode* head;
    
    public:
        // Default constructor
        FileTrie();

        // Add file, ignore case
        void addFile(File* f);

        // Search
        std::unordered_set<File*> getFilesWithPrefix(const std::string& prefix) const;

        // Destructor
        ~FileTrie();
};