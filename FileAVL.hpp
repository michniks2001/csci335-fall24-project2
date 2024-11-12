/**
 * @file FileAVL.hpp
 * @brief Defines the interface for the AVLtree class & implementation of the Node struct
 */

#pragma once
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

#include "File.hpp"
#include <queue>

struct Node {
   size_t size_;    
   std::vector<File*> files_;
   int height_;   // The height of the Node
   Node *left_;   // A pointer to Node's left child
   Node *right_;  // A pointer to Node's right child
   
   // Parameterized constructor for a Node
   Node(File* f, Node* lt=nullptr, Node* rt=nullptr) : size_{f->getSize()}, files_{ {f} }, height_{0}, left_{lt}, right_{rt} {}
};


class FileAVL {
   public:

    /**
    * @brief Retrieves all files in the FileAVL whose file sizes are within [min, max]
    * 
    * @param min The min value of the file size query range.
    * @param max The max value of the file size query range.
    * @return std::vector<File*> storing pointers to all files in the tree within the given range.
    * @note If the query interval is in descending order (ie. the given parameters min >= max), 
            the interval from [max, min] is searched (since max >= min)
    */
   std::vector<File*> query(size_t min, size_t max);

   /**
    * @brief Default Constructor: Construct a new AVLtree object
    */
   FileAVL();

   /**
    * @brief Destroy the AVLtree, deallocating all necessary Nodes
    */
   ~FileAVL();

   // =========== INSERTION & BALANCE  ===========

   /**
    * @brief Inserts a specified value into the AVL tree while maintaining balance
    *    If a duplicate is found, increments the count within the Node of the associated value
    * 
    * @param target The value to be inserted
    * @post Increases the size of the tree by 1
    */
   void insert(File* target);   
   
   /**
    * @brief Determines the height of a given Node 
    * 
    * @param n A pointer to a node to be examined
    * @return The height of the given node, or -1 if given a nullptr
    */
   int height(Node* n) const;

   /**
    * @brief Prints level-order traversal of the tree
    */
   void displayLevelOrder() const;

    /**
    * @brief Prints the unique file sizes of the FileAVL in-order
    */
   void displayInOrder() const;

   /**
    * @brief Returns the size of the AVL tree
    */
   int size() const;

   private:
      static const int ALLOWED_IMBALANCE = 1;
      Node* root_;
      int size_;

      /**
       * @brief Internal routine to insert into a subtree
       * 
       * @param target The value to insert
       * @param subroot The root of the subtree to be inserted into
       * @post Set the new root of the subtree
       */
      void insert(File*& target, Node*& subroot);

      /**
       * @brief Balance the given Node
       * 
       * @param t The Node to be balanced
       */
      void balance(Node* &t);

      /**
       * @brief Prints the level-order traversal of the specified subtree 
       */
      void displayLevelOrder(Node* t) const;

     /**
     * @brief Helper for printInorder(). Prints the unique file sizes in-order given a specified root
     * @param root The root of the tree to be printed
     */
      void displayInOrder(Node* t) const;

      // =========== ROTATIONS  ===========

      /**
       * @brief Rotates a Node with its left child
       * 
       * @param k2 The parent Node to be rotated
       * @post Updates heights and sets new root
       */
      void rotateWithLeftChild(Node*& k2);

      /**
       * @brief Rotates a Node with its right child
       * 
       * @param k2 The parent Node to be rotated
       * @post Updates heights and sets new root
       */
      void rotateWithRightChild(Node*& k1);

      /**
       * @brief Performs a double rotation to fix a left-right imbalance about k3
       * 
       * @param k3 The parent Node with a left-right imbalance
       * @post Updates heights, sets new root
       */
      void doubleWithLeftChlid(Node*& k3);

      /**
       * @brief Performs a double rotation to fix a right-left imbalance about k3
       * 
       * @param k3 The parent Node with a right-left imbalance
       * @post Updates heights, sets new root
       */
      void doubleWithRightChild(Node*& k3);

      /**
       * @brief Destroys the given Node and its children
       * 
       * @param t The node to be deleted
       */
      void deleteTree(Node*& t);
};
