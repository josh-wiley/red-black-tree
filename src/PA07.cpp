/**
 *
 * @file PA07.cpp
 *
 * @brief Driver for red-black tree ADT.
 *
 * @author Josh Wiley
 *
 * @details Generates random data, inserts into red-black trees, and tests
 *          member functions.
 *
 */
//
//  Preprocessor Directives  ///////////////////////////////////////////////////
//
#ifndef PA07_CPP_
#define PA07_CPP_
#define DATA_SET_SIZE 10 // TODO: SET TO 1000
#define DATA_SET_MIN 1
#define DATA_SET_MAX 10000
//
//  Header Files  //////////////////////////////////////////////////////////////
//
#include <iostream>
#include <memory>
#include <algorithm>
#include "utils/data_generator.h"
#include "RedBlackNode/RedBlackNode.h"
//
//  Main Function Implementation  //////////////////////////////////////////////
//
int main()
{
    // Red-black tree.
    auto rbt_root_ptr = std::make_shared< RedBlackNode< unsigned int > >(nullptr, false);

    // Test data.
    auto data_set_ptr = std::make_shared< std::list< unsigned int > >();

    // Generate test data.
    data_generator::generate_random_data(
        DATA_SET_SIZE,
        DATA_SET_MIN,
        DATA_SET_MAX,
        data_set_ptr
    );

    // Iterators.
    auto cursor_it = data_set_ptr->begin();
    auto end_it = data_set_ptr->end();

    // Build tree.
    while(cursor_it != end_it)
    {
        // TODO: REMOVE
        std::cout << "\n\nAdding new item. Root value is "
                  << (rbt_root_ptr->empty() ? 0 : rbt_root_ptr->value())
                  << "\n\n";
        
        // Add item and update.
        rbt_root_ptr->add(*cursor_it);

        // Root fell?
        if (rbt_root_ptr->is_root())
        {
            // TODO: REMOVE
            std::cout << "\n\nUpdating root node pointer to "
                      << rbt_root_ptr->parent()->value()
                      << "...\n\n";

            // Update.
            rbt_root_ptr = rbt_root_ptr->parent();
        }

        // Advance.
        ++cursor_it;
    }

    // Display height.
    std::cout << "\n\nRBT height: " << rbt_root_ptr->height();

    // Display in-order output.
    std::cout << "\n\nRBT in-order:\n";
    rbt_root_ptr->each_inorder([] (auto i) { std::cout << *i << ' '; });

    // Display empty state.
    std::cout << "\n\nRBT empty state: " << rbt_root_ptr->empty();

    // Clear.
    rbt_root_ptr->clear();

    // Display empty state (again).
    std::cout << "\n\nRBT empty state: " << rbt_root_ptr->empty();

    // Padding and flush stream.
    std::cout << '\n' << std::endl;

    // Exit (success).
    return 0;
}
//
//  Terminating Precompiler Directives  ////////////////////////////////////////
//
#endif // PA07_CPP_
//