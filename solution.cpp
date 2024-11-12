#include "FileAVL.hpp"
#include "File.hpp"
#include "FileTrie.hpp"


// Helper function that implements an in-order traversal of the tree to collect thge files within the given range
inline void collectFiles(Node* node, size_t min, size_t max, std::vector<File*>& result) {
    if (node == nullptr) return;

    collectFiles(node->left_, min, max, result);

    for (auto file : node->files_) {
        if (file->getSize() >= min && file->getSize() <= max) {
            result.push_back(file);
        }
    }

    collectFiles(node->right_, min, max, result);

}

// ALL YOUR CODE SHOULD BE IN THIS FILE. NO MODIFICATIONS SHOULD BE MADE TO FILEAVL / FILE CLASSES
// You are permitted to make helper functions (and most likely will need to)
// You must declare them "inline" | declare & implement them at the top of this file, before query()
// Below query(), implement and document all methods declared in FileTrie.hpp

/**
 * @brief Retrieves all files in the FileAVL whose file sizes are within [min, max]
 * 
 * @param min The min value of the file size query range.
 * @param max The max value of the file size query range.
 * @return std::vector<File*> storing pointers to all files in the tree within the given range.
 * @note If the query interval is in descending order (ie. the given parameters min >= max), 
        the interval from [max, min] is searched (since max >= min)
 */
std::vector<File*> FileAVL::query(size_t min, size_t max) {
    std::vector<File*> result;

    if (min >= max) std::swap(min, max);

    collectFiles(root_, min, max, result);

    return result;
}

// FileTrie Implementation




// Constructor
FileTrie::FileTrie() : head(new FileTrieNode('\0')) {}


// addFile
void FileTrie::addFile(File* f) {
    std::string filename = f->getName();
    std::transform(filename.begin(), filename.end(), filename.begin(), std::tolower<char>);
    FileTrieNode* current = head;

    for (char ch : filename) {
        if (current->next.find(ch) == current->next.end()) {
            current->next[ch] = new FileTrieNode(ch);
        }

        current = current->next[ch];
        current->matching.insert(f);
    }
}
