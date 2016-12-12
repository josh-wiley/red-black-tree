/**
 *
 * @file RedBlackNode.cpp
 *
 * @brief Red-black node class implementation.
 *
 * @author Josh Wiley
 *
 * @details Implements the RedBlackNode class.
 *
 */
//
//  Preprocessor Directives  ///////////////////////////////////////////////////
//
#ifndef RED_BLACK_NODE_CPP_
#define RED_BLACK_NODE_CPP_
//
//  Header Files  //////////////////////////////////////////////////////////////
//
#include "RedBlackNode.h"
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Default initializes empty (red) node
 *
 */
template<typename T>
RedBlackNode<T>::RedBlackNode(RedBlackNode* parent_ptr, bool is_red)
    : 
      parent_rawptr_(parent_ptr),
      value_ptr_(nullptr),
      is_red_(is_red),
      left_child_ptr_(nullptr),
      right_child_ptr_(nullptr) {}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Copy-initializes node
 *
 */
template<typename T>
RedBlackNode<T>::RedBlackNode(const RedBlackNode<T>& origin)
    : parent_rawptr_(origin.parent_rawptr_), is_red_(origin.is_red_)
{
    // Is empty?
    if (origin.empty())
    {
        // Default-initialize.
        value_ptr_ = left_child_ptr_ = right_child_ptr_ = nullptr;

        // Abort.
        return;
    }

    // Copy-initialize value.
    value_ptr_ = std::make_shared< T >(*origin.value_ptr);

    // Copy initialize left sub-tree.
    left_child_ptr_ = std::make_shared< RedBlackNode< T > >( 
        *origin.left_child_ptr
    );

    // Copy initialize right sub-tree.
    right_child_ptr_ = std::make_shared< RedBlackNode< T > >( 
        *origin.right_child_ptr
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
RedBlackNode<T>::~RedBlackNode() {}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Returns a boolean value indicating if the node is empty
 *
 * @return Boolean value indicating if the tree is empty
 *
 */
template<typename T>
bool RedBlackNode<T>::empty()
{
    // Empty if no root.
    return value_ptr_ == nullptr;
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
unsigned int RedBlackNode<T>::height()
{
    // Empty?
    if (empty())
    {
        // Return 0.
        return 0;
    }

    // Return.
    return 1 + std::max(
        left_child_ptr_->height(),
        right_child_ptr_->height()
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
unsigned int RedBlackNode<T>::total_nodes()
{
    // Empty?
    if (empty())
    {
        // Return 0.
        return 0;
    }

    // Return.
    return 1 + left_child_ptr_->total_nodes() + right_child_ptr_->total_nodes();
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Returns the value of the node
 *
 * @return Returns the value of the node
 *
 */
template<typename T>
T RedBlackNode<T>::value()
{
    // Return root value.
    return *value_ptr_;
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
void RedBlackNode<T>::clear()
{
    // Reset all pointers.
    value_ptr_ = nullptr;
    left_child_ptr_ = nullptr;
    right_child_ptr_ = nullptr;
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
bool RedBlackNode<T>::contains(T key)
{
    // Return search result.
    return fetch_descendant(key) != nullptr;
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
void RedBlackNode<T>::each_preorder(std::function< void(std::shared_ptr<T>) > iteratee)
{
    // Empty?
    if (empty())
    {
        // Abort.
        return;
    }

    // Process.
    iteratee(value_ptr_);

    // Forward.
    left_child_ptr_->each_preorder(iteratee);
    right_child_ptr_->each_preorder(iteratee);
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
void RedBlackNode<T>::each_inorder(std::function< void(std::shared_ptr<T>) > iteratee)
{
    // Empty?
    if (empty())
    {
        // Abort.
        return;
    }

    // Forward.
    left_child_ptr_->each_inorder(iteratee);

    // Process.
    iteratee(value_ptr_);

    // Forward.
    right_child_ptr_->each_inorder(iteratee);
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
void RedBlackNode<T>::each_postorder(std::function< void(std::shared_ptr<T>) > iteratee)
{
    // Empty?
    if (empty())
    {
        // Abort.
        return;
    }

    // Forward.
    left_child_ptr_->each_postorder(iteratee);
    right_child_ptr_->each_postorder(iteratee);

    // Process.
    iteratee(value_ptr_);
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Adds item with the value of the key parameter to the correct
 *          position in the tree and restructures/repaints the tree to maintain
 *          balance.
 *
 * @param[in] key
 *            Item to add to tree.
 *
 */
template<typename T>
bool RedBlackNode<T>::add(const T& key)
{
    // Empty?
    if (empty())
    {
        // Add node.
        value_ptr_.reset(new T(key));

        // Default-initialize child nodes.
        left_child_ptr_.reset(new RedBlackNode< T >(this, false));
        right_child_ptr_.reset(new RedBlackNode< T >(this, false));

        // Fix-up.
        fixup();

        // Return success.
        return true;
    }

    // 4-node?
    else if (
        // Black node.
        !is_red_() &&

        // Left child is red.
        (left_child_ptr_ != nullptr && left_child_ptr_->is_red()) &&

        // Right child is red.
        (right_child_ptr_ != nullptr && right_child_ptr_->is_red()))
    {
        // Fix-up.
        fixup();
    }

    // Left sub-tree?
    else if (key <= *value_ptr_)
    {
        // Add left.
        return left_child_ptr_->add(key);
    }
    
    // Right sub-tree.
    else
    {
        // Add right.
        return right_child_ptr_->add(key);
    }
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Removes item specified by the value of key from the tree.
 *          (TODO: IMPLEMENT)
 *
 * @param[in] key
 *            Item to remove from the tree.
 *
 */
template<typename T>
bool RedBlackNode<T>::remove(const T& key) {}
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
std::shared_ptr< RedBlackNode< T > > RedBlackNode<T>::fetch_descendant(T key)
{
    // Is empty or equal?
    if (empty())
    {
        // No match.
        return nullptr;
    }
    else if (key == *value_ptr_)
    {
        // Return this.
        return this;
    }
    // Is in left tree?
    else if (key < *value_ptr_)
    {
        // Return result from left tree.
        return left_child_ptr_->value() == key ? left_child_ptr_->value() : left_child_ptr_->fetch_descendant(key);
    }
    // In right tree.
    else
    {
        // Return result from right tree.
        return right_child_ptr_->value() == key ? right_child_ptr_->value() : right_child_ptr_->fetch_descendant(key);
    }
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Returns a boolean value indicating whether or not the node is red.
 *
 * @return Boolean value indicating whether or not the node is red.
 *
 */
template<typename T>
bool RedBlackNode<T>::is_red() const
{
    // Return flag.
    return is_red_;
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Toggles color of node.
 *
 */
template<typename T>
void RedBlackNode<T>::toggle_color()
{
    // Toggle color.
    is_red_ = !is_red_;
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Balances tree (after recolor).
 *
 */
template<typename T>
void RedBlackNode<T>::rotate()
{
    // Root?
    if (parent_rawptr_ == nullptr)
    {
        // TODO: IMPLEMENT
    }

    // Base case.
    if (
        // Parent is 3-node?
        (parent_rawptr_->left_child_ptr_->is_red() || parent_rawptr_->right_child_ptr_->is_red())
    )
    {
        // Done.
        return;
    }

    // Parent is 4-node.
    else
    {
        // Rotate.
    }
}
//
//  Terminating Precompiler Directives  ////////////////////////////////////////
//
#endif // RED_BLACK_NODE_CPP_
//