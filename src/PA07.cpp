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
#define DATA_SET_SIZE 1000
#define DATA_SET_MIN 1
#define DATA_SET_MAX 10000
//
//  Header Files  //////////////////////////////////////////////////////////////
//
#include <iostream>
#include <memory>
#include <algorithm>
#include "utils/data_generator.h"
#include "RedBlackTree/RedBlackTree.h"
//
//  Main Function Implementation  //////////////////////////////////////////////
//
int main()
{
    // Red-black tree.
    auto rbt_ptr = std::make_shared< RedBlackTree< unsigned int > >();

    // Test data.
    auto data_set_ptr = std::shared_ptr< std::list< unsigned int > >(
        new std::list<unsigned int>()
    );

    // Generate test data.
    data_generator::generate_random_data(
        DATA_SET_SIZE,
        DATA_SET_MIN,
        DATA_SET_MAX,
        data_set_ptr
    );

    // Build tree.
    std::for_each(data_set_ptr->begin(), data_set_ptr->end(), [rbt_ptr] (auto i)
    {
        // Add item.
        rbt_ptr->add(i);
    });

    // Display height.
    std::cout << "\n\nRBT height: " << rbt_ptr->height();

    // Display in-order output.
    std::cout << "\n\nRBT in-order:\n";
    rbt_ptr->each_inorder([] (auto i) { std::cout << *i << ' '; });

    // Display empty state.
    std::cout << "\n\nRBT empty state: " << rbt_ptr->empty();

    // Clear.
    rbt_ptr->clear();

    // Display empty state (again).
    std::cout << "\n\nRBT empty state: " << rbt_ptr->empty();

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