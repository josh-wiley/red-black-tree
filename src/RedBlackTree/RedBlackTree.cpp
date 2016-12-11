/**
 *
 * @file RedBlackTree.cpp
 *
 * @brief Red-black tree class implementation.
 *
 * @author Josh Wiley
 *
 * @details Implements the RedBlackTree class.
 *
 */
//
//  Preprocessor Directives  ///////////////////////////////////////////////////
//
#ifndef RED_BLACK_TREE_CPP_
#define RED_BLACK_TREE_CPP_
//
//  Header Files  //////////////////////////////////////////////////////////////
//
#include "RedBlackTree.h"
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Default initializes empty tree
 *
 */
template<typename T>
RedBlackTree<T>::RedBlackTree(RedBlackTree* parent_ptr)
    : 
      parent_rawptr_(parent_ptr),
      root_value_ptr_(nullptr),
      left_tree_ptr_(nullptr),
      right_tree_ptr_(nullptr) {}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Copy-initializes tree
 *
 */
template<typename T>
RedBlackTree<T>::RedBlackTree(const RedBlackTree<T>& origin)
{
    // Copy-initialize parent pointer.
    parent_rawptr_ = origin.parent_rawptr_;

    // Is empty?
    if (origin.empty())
    {
        // Default-initialize.
        root_value_ptr_ = left_tree_ptr_ = right_tree_ptr_ = nullptr;

        // Abort.
        return;
    }

    // Copy-initialize root.
    root_value_ptr_ = std::make_shared< T >(*origin.root_value_ptr);

    // Copy initialize left tree.
    left_tree_ptr_ = std::make_shared< RedBlackTree< T > >( 
        *origin.left_tree_ptr
    );

    // Copy initialize right tree.
    right_tree_ptr_ = std::make_shared< RedBlackTree< T > >( 
        *origin.right_tree_ptr
    );
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Destructor
 *
 */
template<typename T>
RedBlackTree<T>::~RedBlackTree() {}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Returns a boolean value indicating if the tree is empty
 *
 * @return Boolean value indicating if the tree is empty
 *
 */
template<typename T>
bool RedBlackTree<T>::empty()
{
    // Empty if no root.
    return root_value_ptr_ == nullptr;
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Returns a number indicating the current height of the tree
 *
 * @return Integer indicating the current height of the tree
 *
 */
template<typename T>
unsigned int RedBlackTree<T>::height()
{
    // Empty?
    if (empty())
    {
        // Return 0.
        return 0;
    }

    // Return.
    return 1 + std::max(
        left_tree_ptr_->height(),
        right_tree_ptr_->height()
    );
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Returns a number indicating the current number of nodes in the tree
 *
 * @return Integer indicating the current number of nodes in the tree
 *
 */
template<typename T>
unsigned int RedBlackTree<T>::total_nodes()
{
    // Empty?
    if (empty())
    {
        // Return 0.
        return 0;
    }

    // Return.
    return 1 + left_tree_ptr_->total_nodes() + right_tree_ptr_->total_nodes();
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Returns the value of the root node
 *
 * @return Returns the value of the root node
 *
 */
template<typename T>
T RedBlackTree<T>::root_value()
{
    // Return root value.
    return *root_value_ptr_;
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Clears the tree
 *
 */
template<typename T>
void RedBlackTree<T>::clear()
{
    // Reset all pointers.
    root_value_ptr_ = nullptr;
    left_tree_ptr_ = nullptr;
    right_tree_ptr_ = nullptr;
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Searches the tree for the value and returns a boolean value that
 *          represents the results of the search.
 *
 * @param[in] key
 *            Value used for comparison in search.
 *
 * @return Boolean value that represents the results of the search.
 *
 */
template<typename T>
bool RedBlackTree<T>::contains(T key)
{
    // Return search result.
    return fetch_node(key) != nullptr;
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Iterates over the tree in preorder and executes the iteratee on each
 *          item.
 *
 * @param[in] iteratee
 *            Function to execute with each item.
 *
 */
template<typename T>
void RedBlackTree<T>::each_preorder(std::function< void(std::shared_ptr<T>) > iteratee)
{
    // Empty?
    if (empty())
    {
        // Abort.
        return;
    }

    // Process root.
    iteratee(root_value_ptr_);

    // Forward.
    left_tree_ptr_->each_preorder(iteratee);
    right_tree_ptr_->each_preorder(iteratee);
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Iterates over the tree in order and executes the iteratee on each
 *          item.
 *
 * @param[in] iteratee
 *            Function to execute with each item.
 *
 */
template<typename T>
void RedBlackTree<T>::each_inorder(std::function< void(std::shared_ptr<T>) > iteratee)
{
    // Empty?
    if (empty())
    {
        // Abort.
        return;
    }

    // Forward.
    left_tree_ptr_->each_inorder(iteratee);

    // Process root.
    iteratee(root_value_ptr_);

    // Forward
    right_tree_ptr_->each_inorder(iteratee);
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Iterates over the tree in postorder and executes the iteratee on each
 *          item.
 *
 * @param[in] iteratee
 *            Function to execute with each item.
 *
 */
template<typename T>
void RedBlackTree<T>::each_postorder(std::function< void(std::shared_ptr<T>) > iteratee)
{
    // Empty?
    if (empty())
    {
        // Abort.
        return;
    }

    // Forward.
    left_tree_ptr_->each_postorder(iteratee);
    right_tree_ptr_->each_postorder(iteratee);

    // Process root.
    iteratee(root_value_ptr_);
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Adds item with the value of the key parameter to the correct
 *          position in the tree.
 *
 * @param[in] key
 *            Item to add to tree.
 *
 */
template<typename T>
bool RedBlackTree<T>::add(const T& key)
{
    // Empty?
    if (empty())
    {
        // Add as root.
        root_value_ptr_.reset(new T(key));

        // Default-initialize sub-trees.
        left_tree_ptr_.reset(new RedBlackTree< T >(this));
        right_tree_ptr_.reset(new RedBlackTree< T >(this));

        // Return success.
        return true;
    }
    // Left tree?
    else if (key <= *root_value_ptr_)
    {
        // Add left.
        return left_tree_ptr_->add(key);
    }
    // Right tree.
    else
    {
        // Add right.
        return right_tree_ptr_->add(key);
    }
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Removes item specified by the value of key from the tree.
 *
 * @param[in] key
 *            Item to remove from the tree.
 *
 */
template<typename T>
bool RedBlackTree<T>::remove(const T& key) {}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Searches for node with specified value in tree and returns a smart
 *          pointer to it.
 *
 * @param[in] key
 *            Item to search for in the tree.
 *
 */
template<typename T>
RedBlackTree< T >* RedBlackTree<T>::fetch_node(T key)
{
    // Is empty or equal?
    if (empty())
    {
        // No match.
        return nullptr;
    }
    else if (key == *root_value_ptr_)
    {
        // Return this.
        return this;
    }
    // Is in left tree?
    else if (key < *root_value_ptr_)
    {
        // Return result from left tree.
        return left_tree_ptr_->fetch_node(key);
    }
    // In right tree.
    else
    {
        // Return result from right tree.
        return right_tree_ptr_->fetch_node(key);
    }
}
//
//  Terminating Precompiler Directives  ////////////////////////////////////////
//
#endif // RED_BLACK_TREE_CPP_
//