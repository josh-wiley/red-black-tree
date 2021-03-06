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
class RedBlackNode : public std::enable_shared_from_this<RedBlackNode <T> >
{
// Public members.
public:
    RedBlackNode(std::shared_ptr< RedBlackNode< T > > parent_ptr, bool is_red = false); /**< Default constructor */
    RedBlackNode(const RedBlackNode<T>&); /**< Copy constructor */
    ~RedBlackNode(); /**< Destructor */

    bool empty() const; /**< Returns boolean indicating whether the node is empty or not */
    bool is_root() const; /** Returns boolean value whether or not the node is the root */
    std::shared_ptr< RedBlackNode< T > > parent() const; /**< Getter method for raw pointer to parent */
    unsigned int height() const; /**< Returns height of tree from which this node is the root */
    unsigned int total_nodes() const; /**< Returns the total number of nodes in the tree in which this node is the root */
    T value() const; /**< Returns value of node */
    void clear(); /**< Clears node and all sub-trees. */
    bool contains(T) const; /**< Check if the value exists in the tree where this node is the root */
    void each_preorder(std::function< void(std::shared_ptr<T>) >); /**< Executes provided function on each item in pre-order. */
    void each_inorder(std::function< void(std::shared_ptr<T>) >); /**< Executes provided function on each item in-order. */
    void each_postorder(std::function< void(std::shared_ptr<T>) >); /**< Executes provided function on each item in post-order. */
    bool add(const T&); /**< Adds item to correct place in tree (where this node is the root) and returns boolean value indicating success */
    bool remove(const T&); /**< Removes value from tree and returns boolean value indicating success */

// Private members.
private:
    std::shared_ptr< RedBlackNode< T > > parent_ptr_; /**< Smart pointer to parent. */
    std::shared_ptr< T > value_ptr_; /** Smart pointer to value of root node */
    bool is_red_; /**< Boolean value indicating whether the node is red. */
    std::shared_ptr< RedBlackNode< T > > left_child_ptr_; /**< Smart pointer to the left child */
    std::shared_ptr< RedBlackNode< T > > right_child_ptr_; /**< Smart pointer to the right child */

    std::shared_ptr< RedBlackNode< T > > fetch_descendant(T); /**< Search for child node with given value and return pointer to node */
    void fixup(); /**< Re-balances the tree initiated from this node */
    void rotate_left(); /**< Rotates left with this node as the pivot */
    void rotate_right(); /**< Rotates right with this node as the pivot */
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