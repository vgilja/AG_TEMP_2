#include <iostream>
#include "Maze.h"
#include "Game.h"
#include "testing.h"

int main(int argc, const char * argv[]) {

  /* Note: you can test for each problem by calling the main program with the test_name argument as
  /  was possible for the last few homework assignments.  You can also modify this main function to
  /  hard code the test_name variable if you find that easier.  The autograder uses a clean version of
  /  this file to test.
  /
  / test_name options:
  /             "compile" - basic compilation test
  /             "print" - problem 1 (autograder matches output)
  /             "is_begin" - problem 2 (prints passing message)
  /             "random_player" - problem 3 (prints passing message)
  /             "efficient_player" - problem 4 (prints passing message)
  /             "efficient_player_exception" - problem 5 (prints passing message)
  /             "max_turns" - problem 6 (prints passing message)
 */

  if (argc > 1) {
    std::string test_name(argv[1]);

    if ("compile" == test_name) {
      std::cout << "Compiled OK.\n";
      return 0;
    }

    // Problem 1
    else if ("print" == test_name) {
      test_print_maze_with_player();
      return 0;
    }

    // Problem 2
    else if ("is_begin" == test_name) {
      if (test_is_begin()) {
        std::cout << "Full Credit" << std::endl;
        return 0;
      } else return 1;
    }

    // Problem 3
    else if ("random_player" == test_name) {
      size_t num_tests_passed = test_random_player();
      if (num_tests_passed == 2) {
        std::cout << "Full Credit for Random Player" << std::endl;
        return 0;
      }
      std::cout << "Passed " << num_tests_passed << " of 2 tests, partial credit if > 0" << std::endl;
      return 1;
    }

    // Problem 4
    else if ("efficient_player" == test_name) {
      size_t mazes_passed = test_efficient_player();
      if (3 == mazes_passed) {
        std::cout << "PASSED: Full credit for Efficient Player" << std::endl;
        return 0;
      }
      else {
        std::cout << "FAILED: " << mazes_passed << " of 3 mazes passed, partial credit if greater than 0";
        return 1;
      }
    }

    // Problem 5
    else if ("efficient_player_exception" == test_name) {
      if (test_efficient_player_exception()) {
        std::cout << "PASSED";
        return 0;
      }
      else {
        std::cout << "FAILED: Efficient player returned without an exception";
      }
    }

    // Problem 6
    else if ("max_turns" == test_name) {
      if (test_max_turns()) {
        std::cout << "PASSED";
        return 0;
      }
      else {
        std::cout << "FAILED: No partial credit";
      }
    }
  }
  return 1; // no test specified!
}
