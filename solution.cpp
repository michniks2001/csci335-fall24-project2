#include "FileAVL.hpp"
#include "File.hpp"
#include "FileTrie.hpp"


// Helper function that implements an in-order traversal of the tree to collect the files within the given range
inline void collectFilesWithinRange(Node* node, size_t min, size_t max, std::vector<File*>& result) {
    if (node == nullptr) return;

    collectFilesWithinRange(node->left_, min, max, result);

    for (auto file : node->files_) {
        if (file->getSize() >= min && file->getSize() <= max) {
            result.push_back(file);
        }
    }

    collectFilesWithinRange(node->right_, min, max, result);

}

// Helper function for collecting each file from the given node
inline void collectFilesFromNode(FileTrieNode* node, std::unordered_set<File*>& results) {
    results.insert(node->matching.begin(), node->matching.end());

    for (const auto& pair : node->next)
        collectFilesFromNode(pair.second, results);
}

// Helper function that recursively deletes nodes
inline void deleteNode(FileTrieNode* node) {
    if (!node) return;

    for (auto& pair : node->next) {
        deleteNode(pair.second);
    }

    node->next.clear();

    delete node;
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

    collectFilesWithinRange(root_, min, max, result);

    return result;
}

// FileTrie Implementation




// Constructor
FileTrie::FileTrie() : head(new FileTrieNode('\0')) {}


// addFile
void FileTrie::addFile(File* f) {
    std::string filename = "";

    for (auto ch : f->getName()) {
        filename += std::tolower(ch);
    }

    FileTrieNode* current = head;

    for (char ch : filename) {
        if (current->next.find(ch) == current->next.end()) {
            current->next[ch] = new FileTrieNode(ch);
        }

        current = current->next[ch];
        current->matching.insert(f);
    }
}

std::unordered_set<File*> FileTrie::getFilesWithPrefix(const std::string& prefix) const {
    std::unordered_set<File*> results;
    FileTrieNode* current = head;

    for (char ch : prefix) {
        char lowerCh = std::tolower(ch);

        if (current->next.find(lowerCh) == current->next.end()) {
            return results;
        }
        
        current = current->next[lowerCh];
    }

    collectFilesFromNode(current, results);
    return results;
}

FileTrie::~FileTrie() {
    if (head) {
        deleteNode(head);
    }
}


/* int main() {


    // Create files
    File* file1 = new File("test.txt", "test.txt contents", nullptr); 
    File* file2 = new File("testing.txt", "testing.txt contents", nullptr); 
    File* file3 = new File("temp.txt", "temp.txt contents", nullptr); 
    File* file4 = new File("teaser.txt", "teaser.txt contents", nullptr); 
    File* file5 = new File("example.txt", "example.txt contents", nullptr); 
    FileTrie t;

    std::cout << "----------Testing FileTrie Class----------" << std::endl;

    std::cout << "Adding files to trie..." << std::endl;
    t.addFile(file1);
    t.addFile(file2);
    t.addFile(file3);
    t.addFile(file4);
    t.addFile(file5);
    std::cout << "Files added successfully!" << std::endl;

    std::cout << "Searching for files with prefix 'te':" << std::endl;
    auto results1 = t.getFilesWithPrefix("te");
    for (const auto& file : results1) {
        std::cout << "Found: " << file->getName() << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Searching for files with prefix 'TE':" << std::endl;
    auto results2 = t.getFilesWithPrefix("TE");
    for (const auto& file : results2) {
        std::cout << "Found: " << file->getName() << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Searching for files with prefix 'xyz':" << std::endl;
    auto results3 = t.getFilesWithPrefix("xyz");
    for (const auto& file : results3) {
        std::cout << "Found: " << file->getName() << std::endl;
    }
    
    if (results3.empty())
        std::cout << "Empty" << std::endl;
    std::cout << std::endl;

    std::cout << "Searching for files with prefix 't':" << std::endl;
    auto results4 = t.getFilesWithPrefix("t");
    for (const auto& file : results4) {
        std::cout << "Found: " << file->getName() << std::endl;
    }
    std::cout << std::endl;

    delete file1;
    delete file2;
    delete file3;
    delete file4;
    delete file5;

    return 0;
} */
