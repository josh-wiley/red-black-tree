/**
 *
 * @file data_generator.cpp
 *
 * @brief Implements test generation utility functions.
 *
 * @author Josh Wiley
 *
 * @details Provides convenience functions for generating test data sets.
 *
 */
//
//  Preprocessor Directives  ///////////////////////////////////////////////////
//
#ifndef DATA_GENERATOR_CPP_
#define DATA_GENERATOR_CPP_
//
//  Header Files  //////////////////////////////////////////////////////////////
//
#include "data_generator.h"
//
//  Function Implementation  /////////////////////////////////////////////////
//
/**
 *
 * @brief Generates random data and places into provided list
 *
 * @details Generates the specified amount of random, unsigned integers and
 *          inserts into the data set
 *
 * @param[in] size
 *            The number of random values generated and final size of the
 *            data set
 *
 * @param[in] min
 *            Minimum value for random data
 *
 * @param[in] max
 *            Maximum value for random data
 *
 * @param[out] data_set_ptr
 *             A shared pointer to the container that data will be placed into
 *
 */
void data_generator::generate_random_data(
  size_t size,
  size_t min,
  size_t max,
  std::shared_ptr< std::list< unsigned int > > data_set_ptr
)
{
  // Ensure data set is empty.
  data_set_ptr->clear();

  // Seed the random value generator.
  std::srand(
    std::chrono::high_resolution_clock::now()
    .time_since_epoch()
    .count()
  );

  // Value buffer.
  auto rnd_value = (unsigned int) std::rand() % (max + 1 - min) + min;

  // Push first value.
  data_set_ptr->push_back(rnd_value);

  // Iterators.
  auto ds_cursor_it = data_set_ptr->begin();
  auto ds_end_it = data_set_ptr->end();

  // Flag.
  auto is_value_unique = false;

  // Generate data set.
  for (unsigned int i = 0; i < size - 1; i++)
  {
    // Flag.
    is_value_unique = false;

    // Ensure item is unique before adding.
    while (!is_value_unique)
    {
      // Generate new value.
      rnd_value = (unsigned int) std::rand() % (max + 1 - min) + min;

      // Flag.
      is_value_unique = true;

      // Is unique?
      while (ds_cursor_it != ds_end_it)
      {
        // Is new value equal to current value?
        if (rnd_value == *ds_cursor_it)
        {
          // Flag.
          is_value_unique = false;

          // Break.
          break;
        }
        
        // Advance.
        ++ds_cursor_it;
      }

      // Reset cursor.
      ds_cursor_it = data_set_ptr->begin();
    }

    // Push random value.
    data_set_ptr->push_back(rnd_value);
  }
}
//
//  Terminating Precompiler Directives  ////////////////////////////////////////
//
#endif // DATA_GENERATOR_CPP_
//
