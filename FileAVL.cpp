#include "FileAVL.hpp"

/**
 * @brief Determines the height of a given Node 
 * 
 * @param n A pointer to a node to be examined
 * @return The height of the given node, or -1 if given a nullptr
 */
int FileAVL::height(Node* n) const {
   if (n == nullptr) {
      return -1;
   }
   return n->height_;
}

/**
 * @brief Returns the size of the AVL tree
 */
int FileAVL::size() const {
   return size_;
}

/**
 * @brief Prints the value of the specified Node t and its children using level-order traversal
 */
void FileAVL::displayLevelOrder(Node* t) const {
    if (!t) { return; }
    
    std::queue<Node*> current, next;
    current.push(t);

    while (!current.empty()) {
        while (!current.empty()) {
            Node*& front = current.front();
            if (front->left_) { next.push(front->left_); }   
            if (front->right_) { next.push(front->right_); }
            std::cout << front->size_ << " ";
            current.pop();
        }
        std::cout << std::endl;
        current = std::move(next);
    }
}

/**
* @brief Prints the level-order traversal of the specified subtree 
*/
void FileAVL::displayLevelOrder() const {
   displayLevelOrder(root_);   
}

/**
 * @brief Wrapper for printing the unique file sizes of the FileAVL in-order
 */
void FileAVL::displayInOrder() const {
    if (!root_) { return; }
    displayInOrder(root_);
    std::cout << std::endl;
}

/**
 * @brief Helper for displayInOrder(). Prints the unique file sizes in-order given a specified root
 * @param root The root of the tree to be printed
 */
void FileAVL::displayInOrder(Node* root) const {
    if (!root) { return; }
    
    displayInOrder(root->left_);
    std::cout << root->files_[0]->getSize() << " ";
    displayInOrder(root->right_);
}

/**
 * @brief Default Constructor: Construct a new FileAVL object
 */
FileAVL::FileAVL() : root_ {nullptr}, size_{0} {}

 /**
 * @brief Destroys the given Node and its children
 * 
 * @param t The node to be deleted
 */
void FileAVL::deleteTree(Node*& t) {
   if (t == nullptr) { return; }
   deleteTree(t->left_);
   deleteTree(t->right_);
   delete t;
   t = nullptr;
}

/**
 * @brief Destroy the FileAVL, deallocating all necessary Nodes
 */
FileAVL::~FileAVL() {
   deleteTree(root_);
}

/**
 * @brief Inserts a specified value into the AVL tree while maintaining balance
 *    If a duplicate is found, increments the count within the Node of the associated value
 * 
 * @param target The value to be inserted
 * @post Increases the size of the tree by 1
 */
void FileAVL::insert(File* target) {
   insert(target, root_);
   size_++;
}

/**
 * @brief Internal routine to insert into a subtree
 * 
 * @param target The value to insert
 * @param subroot The root of the subtree to be inserted into
 * @post Set the new root of the subtree
 */
void FileAVL::insert(File*& target, Node*& subroot) {
   if (subroot == nullptr) {
      subroot = new Node({ target });
   } else if (target->getSize() == subroot->files_.front()->getSize()) {
      subroot->files_.push_back(target);
   } else if (target->getSize() < subroot->files_.front()->getSize()) {
      insert(target, subroot->left_);
   } else {
      insert(target, subroot->right_);
   }

   balance(subroot);
}

/**
 * @brief Balance the given Node
 * 
 * @param t The Node to be balanced
 */
void FileAVL::balance(Node* &t) {
   if (t == nullptr) {
      return ;
   }

   if ( height(t->left_) - height(t->right_) > ALLOWED_IMBALANCE) {
      if ( height( t->left_->left_ ) >= height( t->left_->right_ ) ) {
         rotateWithLeftChild(t);
      } else {
         doubleWithLeftChlid(t);
      }
   } else {
      if (  height( t->right_ ) - height( t->left_ ) > ALLOWED_IMBALANCE ) {
         if( height( t->right_->right_ ) >= height( t->right_->left_ ) )
            rotateWithRightChild( t );
         else {
            doubleWithRightChild( t );
         }
      }
   }

   t->height_ = std::max( height( t->left_ ), height( t->right_ ) ) + 1;
}

/**
 * @brief Performs a rotation on k2 with its left child
 * 
 * @param k2 The node to be brought down to its left child
 * @post k2 is set to the rotated root (ie. its initial left child); 
 * Both nodes roots are updated to reflect the rotation
 */
void FileAVL::rotateWithLeftChild(Node*& k2) {
   Node* k1 = k2->left_;
   k2->left_ = k1->right_;
   k1->right_ = k2;

   k2->height_ = std::max( height( k2->left_ ), height( k2->right_ ) ) + 1;
   k1->height_ = std::max( height( k1->left_ ), k2->height_ ) + 1;
   k2 = k1;
}

/**
 * @brief Performs a rotation on k1 with its right child
 * 
 * @param k1 The node to be brought down to its right child
 * @post k1 is set to the rotated root (ie. its initial right child); 
 * Both nodes roots are updated to reflect the rotation
 */
void FileAVL::rotateWithRightChild(Node*& k1) {
   Node* k2 = k1->right_;
   k1->right_ = k2->left_;
   k2->left_ = k1;
   k1->height_ = 1 + std::max( height( k1->left_ ), height( k1->right_ ));
   k2->height_ = 1 + std::max( k1->height_, height(k2->right_) );
   k1 = k2;
}

/**
 * @brief Performs a double rotation to fix a left-right imbalance about k3
 * 
 * @param k3 The parent Node with a left-right imbalance
 * @post Updates heights, sets new root
 */
void FileAVL::doubleWithLeftChlid(Node*& k3) {
   rotateWithRightChild( k3->left_ );
   rotateWithLeftChild( k3 );
}

/**
 * @brief Performs a double rotation to fix a right-left imbalance about k3
 * 
 * @param k3 The parent Node with a right-left imbalance
 * @post Updates heights, sets new root
 */
void FileAVL::doubleWithRightChild(Node*& k3) {
   rotateWithLeftChild(k3->right_);
   rotateWithRightChild(k3);
}