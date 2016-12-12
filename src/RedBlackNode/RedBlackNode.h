/**
 *
 * @file RedBlackNode.h
 *
 * @brief Red-black node class definition.
 *
 * @author Josh Wiley
 *
 * @details Defines the RedBlackNode class.
 *
 */
//
//  Preprocessor Directives  ///////////////////////////////////////////////////
//
#ifndef RED_BLACK_NODE_H_
#define RED_BLACK_NODE_H_
//
//  Header Files  //////////////////////////////////////////////////////////////
//
#include <memory>
#include <algorithm>
#include <functional>
//
//  Class Definition  //////////////////////////////////////////////////////////
//
template<class T>
class RedBlackNode
{
// Public members.
public:
    RedBlackNode(RedBlackNode* parent_ptr = nullptr, bool is_red = true); /**< Default constructor */
    RedBlackNode(const RedBlackNode<T>&); /**< Copy constructor */
    ~RedBlackNode(); /**< Destructor */

    bool empty(); /**< Returns boolean indicating whether the node is empty or not */
    unsigned int height(); /**< Returns height of tree from which this node is the root */
    unsigned int total_nodes(); /**< Returns the total number of nodes in the tree in which this node is the root */
    T value(); /**< Returns value of node */
    void clear(); /**< Clears node and all sub-trees. */
    bool contains(T); /**< Check if the value exists in the tree where this node is the root */
    void each_preorder(std::function< void(std::shared_ptr<T>) >); /**< Executes provided function on each item in pre-order. */
    void each_inorder(std::function< void(std::shared_ptr<T>) >); /**< Executes provided function on each item in-order. */
    void each_postorder(std::function< void(std::shared_ptr<T>) >); /**< Executes provided function on each item in post-order. */
    bool add(const T&); /**< Adds item to correct place in tree (where this node is the root) and returns boolean value indicating success */
    bool remove(const T&); /**< Removes value from tree and returns boolean value indicating success */

// Private members.
private:
    RedBlackNode< T >* parent_rawptr_; /**< Smart pointer to parent. */
    std::shared_ptr< T > value_ptr_; /** Smart pointer to value of root node */
    bool is_red_; /**< Boolean value indicating whether the node is red. */
    std::shared_ptr< RedBlackNode< T > > left_child_ptr_; /**< Smart pointer to the left child */
    std::shared_ptr< RedBlackNode< T > > right_child_ptr_; /**< Smart pointer to the right child */

    std::shared_ptr< RedBlackNode< T > > fetch_descendant(T); /**< Search for child node with given value and return pointer to node */
    bool is_red() const; /**< Returns boolean value indicating whether the node is red. */
    void toggle_color(); /**< Toggles the color of the root item. */
};
//
//  Implementation Files  //////////////////////////////////////////////////////
//
#include "RedBlackNode.cpp"
//
//  Terminating Precompiler Directives  ////////////////////////////////////////
//
#endif // RED_BLACK_NODE_H_
//