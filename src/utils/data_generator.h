/**
 *
 * @file data_generator.h
 *
 * @brief Namespace for test data generation utilities.
 *
 * @author Josh Wiley
 *
 * @details Provides convenience functions for generating test data sets.
 *
 */
//
//  Preprocessor Directives  ///////////////////////////////////////////////////
//
#ifndef DATA_GENERATOR_H_
#define DATA_GENERATOR_H_
//
//  Header Files  //////////////////////////////////////////////////////////////
//
#include <cstdlib>
#include <chrono>
#include <list>
#include <memory>
//
//  Namespace Definition  //////////////////////////////////////////////////////
//
namespace data_generator
{
  // Generate random integer data set.
  void generate_random_data(
    size_t,
    size_t,
    size_t,
    std::shared_ptr< std::list< unsigned int > >
  ); /**< Generates random numbers and stores in list pointer parameter. */
}
//
//  Terminating Precompiler Directives  ////////////////////////////////////////
//
#endif // DATA_SET_GENERATOR_H_
//
