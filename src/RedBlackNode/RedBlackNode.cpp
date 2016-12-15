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
    : parent_rawptr_(parent_ptr), is_red_(is_red)
{
    // Initialize smart pointers.
    value_ptr_ = nullptr;
    left_child_ptr_ = nullptr;
    right_child_ptr_ = nullptr;
}
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
    // Copy smart pointers.
    value_ptr_ = origin.value_ptr_;
    left_child_ptr_ = origin.left_child_ptr_;
    right_child_ptr_ = origin.right_child_ptr_;
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
bool RedBlackNode<T>::empty() const
{
    // Empty if no value.
    return !value_ptr_;
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Returns a raw pointer to parent node
 *
 * @return Raw pointer to parent node
 *
 */
template<typename T>
RedBlackNode< T >* RedBlackNode< T >::parent() const
{
    // Return raw pointer to parent.
    return parent_rawptr_;
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
T RedBlackNode<T>::value() const
{
    // Return root value.
    return value_ptr_ ? *value_ptr_ : T();
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
        value_ptr_ = std::make_shared< T >(key);

        // Make red.
        is_red_ = true;

        // Default-initialize child nodes.
        left_child_ptr_ = std::make_shared< RedBlackNode< T > >(this, false);
        right_child_ptr_ = std::make_shared< RedBlackNode< T > >(this, false);

        // TODO: REMOVE
        std::cout << "\n\nAdded.\n"
                  << "Value: " << value() << '\n';
        if (parent())
        {
            std::cout << "Parent: " << parent()->value() << '\n';
        }
        std::cout << '\n';
        

        // Fix-up.
        fixup();

        // Return success.
        return true;
    }

    // Left sub-tree?
    else if (key <= *value_ptr_)
    {
        // TODO: REMOVE
        std::cout << "left ";

        // Add left.
        return left_child_ptr_->add(key);
    }
    
    // Right sub-tree.
    else
    {
        // TODO: REMOVE
        std::cout << "right ";

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
bool RedBlackNode<T>::remove(const T& key) { return false; }
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
 * @details Balances tree (after recolor).
 *
 */
template<typename T>
void RedBlackNode<T>::fixup()
{
    // Root?
    if (!parent_rawptr_)
    {
        // Make black.
        is_red_ = false;
    }

    // "Red" violation (node and parent are both red).
    else if (is_red_ && parent_rawptr_->is_red_)
    {
        // TODO: REMOVE
        std::cout << "\n\nRed violation...\n\n";

        // Get grandparent.
        auto grandparent_rawptr = parent_rawptr_->parent_rawptr_;

        // Get uncle.
        auto uncle_ptr = grandparent_rawptr->left_child_ptr_.get() == parent_rawptr_ ? grandparent_rawptr->right_child_ptr_ : grandparent_rawptr->left_child_ptr_;

        // Left child?
        auto is_left_child = parent_rawptr_->left_child_ptr_.get() == this;

        // Red uncle?
        if (uncle_ptr && uncle_ptr->is_red_)
        {
            // Push "red" violation up the tree.
            parent_rawptr_->is_red_ = false;
            uncle_ptr->is_red_ = false;
            grandparent_rawptr->is_red_ = true;

            // Fixup at grandparent.
            grandparent_rawptr->fixup();
        }

        // No uncle or uncle is black.
        else
        {
            // Outer child (left child of left child or right child of right child)?
            if (
                (is_left_child && grandparent_rawptr->left_child_ptr_.get() == parent_rawptr_) ||
                (!is_left_child && grandparent_rawptr->right_child_ptr_.get() == parent_rawptr_)
            )
            {
                // Color parent black and grandparent red.
                parent_rawptr_->is_red_ = false;
                grandparent_rawptr->is_red_ = true;

                // TODO: REMOVE
                std::cout << "\n\nRotating parent inward...\n\n";

                // Rotate inward.
                is_left_child ? parent_rawptr_->rotate_right() : parent_rawptr_->rotate_left();
            }

            // Inner child.
            else
            {
                // TODO: REMOVE
                std::cout << "\n\nRotating outward...\n\n";

                // Rotate outward about this node.
                is_left_child ? rotate_right() : rotate_left();

                // Fix as if case #2.
                is_red_ = false;
                parent_rawptr_->is_red_ = true;

                // TODO: REMOVE
                std::cout << "\n\nRotating inward...\n\n";

                // Rotate inward about this node.
                parent_rawptr_->left_child_ptr_.get() == this ? rotate_right() : rotate_left();
            }
        }

    }
}
//
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Rotate left about this node.
 *
 */
template<typename T>
void RedBlackNode<T>::rotate_left()
{
    // Save grandparent.
    auto grandparent_rawptr = (parent_rawptr_->parent_rawptr_);

    // TODO: REMOVE
    std::cout << "\n\nGot grandparent: " << (grandparent_rawptr != nullptr ? grandparent_rawptr->value() : T()) << "\n\n";

    // Is parent left child?
    auto is_parent_left_child = grandparent_rawptr != nullptr && grandparent_rawptr->left_child_ptr_.get() == parent_rawptr_;

    // TODO: REMOVE
    std::cout << "\n\nParent is " << (is_parent_left_child ? "left" : "right") << "child\n\n";

    // TODO: REMOVE
    std::cout << "\n\nBefore left rotation.\n"
                << "Value: " << value() << '\n';
    if (left_child_ptr_)
    {
        std::cout << "Left child: " << left_child_ptr_->value() << '\n';
    }
    if (right_child_ptr_)
    {
        std::cout << "Right child: " << right_child_ptr_->value() << '\n';
    }
    if (parent())
    {
        std::cout << "Parent: " << parent()->value() << '\n';

        if (parent()->left_child_ptr_)
        {
            std::cout << "Parent left child: " << parent()->left_child_ptr_->value() << '\n';
        }
        if (parent()->right_child_ptr_)
        {
            std::cout << "Parent right child: " << parent()->right_child_ptr_->value() << '\n';
        }
    }
    if (grandparent_rawptr != nullptr)
    {
        std::cout << "Grandparent: " << grandparent_rawptr->value() << '\n';

        if (grandparent_rawptr->left_child_ptr_)
        {
            std::cout << "Grandparent left child: " << grandparent_rawptr->left_child_ptr_->value() << '\n';
        }
        if (grandparent_rawptr->right_child_ptr_)
        {
            std::cout << "Grandparent right child: " << grandparent_rawptr->right_child_ptr_->value() << '\n';
        }
        
    }
    std::cout << '\n';

    // TODO: REMOVE
    std::cout << "\n\nakagami_distribution";

    // Parent adopts (left) child.
    parent_rawptr_->right_child_ptr_ = left_child_ptr_;

    // Has left child?
    if (left_child_ptr_)
    {
        // Link.
        left_child_ptr_->parent_rawptr_ = (parent_rawptr_->right_child_ptr_.get());
    }

    // Parent becomes (left) child.
    left_child_ptr_ = std::make_shared< RedBlackNode< T > >(*parent_rawptr_);
    parent_rawptr_ = (left_child_ptr_->parent_rawptr_);
    left_child_ptr_->parent_rawptr_ = this;

    // Grandparent?
    if (grandparent_rawptr != nullptr)
    {
        // Bind granparent to new child.
        (is_parent_left_child ? grandparent_rawptr->left_child_ptr_ : grandparent_rawptr->right_child_ptr_) = std::make_shared< RedBlackNode< T > >(*this);
    }

    // TODO: REMOVE
    std::cout << "\n\nAfter left rotation.\n"
                << "Value: " << value() << '\n';
    if (left_child_ptr_)
    {
        std::cout << "Left child: " << left_child_ptr_->value() << '\n';
    }
    if (right_child_ptr_)
    {
        std::cout << "Right child: " << right_child_ptr_->value() << '\n';
    }
    if (parent())
    {
        std::cout << "Parent: " << parent()->value() << '\n';

        if (parent()->left_child_ptr_)
        {
            std::cout << "Parent left child: " << parent()->left_child_ptr_->value() << '\n';
        }
        if (parent()->right_child_ptr_)
        {
            std::cout << "Parent right child: " << parent()->right_child_ptr_->value() << '\n';
        }
    }
    if (grandparent_rawptr != nullptr)
    {
        std::cout << "Grandparent: " << grandparent_rawptr->value() << '\n';

        if (grandparent_rawptr->left_child_ptr_)
        {
            std::cout << "Grandparent left child: " << grandparent_rawptr->left_child_ptr_->value() << '\n';
        }
        if (grandparent_rawptr->right_child_ptr_)
        {
            std::cout << "Grandparent right child: " << grandparent_rawptr->right_child_ptr_->value() << '\n';
        }
        
    }
    std::cout << '\n';
}
//  Class Member Implementation  ///////////////////////////////////////////////
//
/**
 *
 * @details Rotate right about this node.
 *
 */
template<typename T>
void RedBlackNode<T>::rotate_right()
{
    // Save grandparent.
    auto grandparent_rawptr = (parent_rawptr_->parent_rawptr_);

    // Is parent left child?
    auto is_parent_left_child = grandparent_rawptr != nullptr && grandparent_rawptr->left_child_ptr_.get() == parent_rawptr_;

    // TODO: REMOVE
    std::cout << "\n\nBefore right rotation.\n"
                << "Value: " << value() << '\n';
    if (left_child_ptr_)
    {
        std::cout << "Left child: " << left_child_ptr_->value() << '\n';
    }
    if (right_child_ptr_)
    {
        std::cout << "Right child: " << right_child_ptr_->value() << '\n';
    }
    if (parent())
    {
        std::cout << "Parent: " << parent()->value() << '\n';

        if (parent()->left_child_ptr_)
        {
            std::cout << "Parent left child: " << parent()->left_child_ptr_->value() << '\n';
        }
        if (parent()->right_child_ptr_)
        {
            std::cout << "Parent right child: " << parent()->right_child_ptr_->value() << '\n';
        }
    }
    if (grandparent_rawptr != nullptr)
    {
        std::cout << "Grandparent: " << grandparent_rawptr->value() << '\n';

        if (grandparent_rawptr->left_child_ptr_)
        {
            std::cout << "Grandparent left child: " << grandparent_rawptr->left_child_ptr_->value() << '\n';
        }
        if (grandparent_rawptr->right_child_ptr_)
        {
            std::cout << "Grandparent right child: " << grandparent_rawptr->right_child_ptr_->value() << '\n';
        }
        
    }
    std::cout << '\n';

    // Parent adopts (right) child.
    parent_rawptr_->left_child_ptr_ = right_child_ptr_;

    // Has right child?
    if (right_child_ptr_)
    {
        // Link.
        right_child_ptr_->parent_rawptr_ = (parent_rawptr_->left_child_ptr_.get());
    }

    // Parent becomes (right) child.
    right_child_ptr_ = std::make_shared< RedBlackNode< T > >(*parent_rawptr_);
    parent_rawptr_ = (right_child_ptr_->parent_rawptr_);
    right_child_ptr_->parent_rawptr_ = this;

    // Grandparent?
    if (grandparent_rawptr != nullptr)
    {
        // Bind granparent to new child.
        (is_parent_left_child ? grandparent_rawptr->left_child_ptr_ : grandparent_rawptr->right_child_ptr_) = std::make_shared< RedBlackNode< T > >(*this);
    }

    // TODO: REMOVE
    std::cout << "\n\nAfter right rotation.\n"
                << "Value: " << value() << '\n';
    if (left_child_ptr_)
    {
        std::cout << "Left child: " << left_child_ptr_->value() << '\n';
    }
    if (right_child_ptr_)
    {
        std::cout << "Right child: " << right_child_ptr_->value() << '\n';
    }
    if (parent())
    {
        std::cout << "Parent: " << parent()->value() << '\n';

        if (parent()->left_child_ptr_)
        {
            std::cout << "Parent left child: " << parent()->left_child_ptr_->value() << '\n';
        }
        if (parent()->right_child_ptr_)
        {
            std::cout << "Parent right child: " << parent()->right_child_ptr_->value() << '\n';
        }
    }
    if (grandparent_rawptr != nullptr)
    {
        std::cout << "Grandparent: " << grandparent_rawptr->value() << '\n';

        if (grandparent_rawptr->left_child_ptr_)
        {
            std::cout << "Grandparent left child: " << grandparent_rawptr->left_child_ptr_->value() << '\n';
        }
        if (grandparent_rawptr->right_child_ptr_)
        {
            std::cout << "Grandparent right child: " << grandparent_rawptr->right_child_ptr_->value() << '\n';
        }
        
    }
    std::cout << '\n';
}
//
//  Terminating Precompiler Directives  ////////////////////////////////////////
//
#endif // RED_BLACK_NODE_CPP_
//