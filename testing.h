//
// Created by Vikash Gilja on 6/9/21.
//

#ifndef ECE17_SP21_FINAL_TESTING_H
#define ECE17_SP21_FINAL_TESTING_H

#include "Maze.h"
#include "Game.h"
#include <string>
#include <sstream>

std::stringstream maze1("BOOOX\n"
                  "OXXXX\n"
                  "OOXOE\n"
                  "XOOOX");
std::stringstream maze2("XOOOO\n"
                  "OOXXO\n"
                  "BOXOE\n"
                  "XOXOX");
std::stringstream mazeImpossible1("XOOOO\n"
                            "XOXXO\n"
                            "BXXOE\n"
                            "XOXOX");
std::stringstream mazeImpossible2("XOOOO\n"
                            "XXXXO\n"
                            "BOXOE\n"
                            "XOXOX");

void test_print_maze_with_player() {
  Maze maze;
  maze.PrintMazeWithPlayer(Maze::Coordinate(1, 0));
  maze.PrintMazeWithPlayer(Maze::Coordinate(1, 1));
  maze.PrintMazeWithPlayer(Maze::Coordinate(2, 1));

  std::stringstream mazeStream(std::string("OXOX\nBEOX\nXOOO"));
  Maze maze2(&mazeStream);
  maze2.PrintMazeWithPlayer(Maze::Coordinate(2, 0));
  maze2.PrintMazeWithPlayer(Maze::Coordinate(1, 1));
  maze2.PrintMazeWithPlayer(Maze::Coordinate(3, 2));

}

void test_print_message(bool &passed, bool test, std::string msg) {
  if(test) std::cout << "PASSED: ";
  else std::cout << "FAILED: ";
  std::cout << msg << std::endl;
  passed = passed & test;
}

bool test_is_begin() {
  bool passed = true;
  Maze maze;
  test_print_message(passed,
                     maze.IsBegin(Maze::Coordinate(0,2)),
                     " (1) Default maze begins at 0, 2");

  test_print_message(passed,
                     !maze.IsBegin(Maze::Coordinate(1,0)),
                     " (2) Default maze does not begin at 1, 0");

  test_print_message(passed,
                     !maze.IsBegin(Maze::Coordinate(1,10)),
                     " (3) Default maze does not begin at 1, 10");

  std::stringstream mazeStream(std::string("OXOX\nBEOX\nXOOO"));
  Maze maze2(&mazeStream);
  test_print_message(passed,
                     maze2.IsBegin(Maze::Coordinate(0,1)),
                     " (4) Specified maze begins at 0, 1");

  test_print_message(passed,
                     !maze2.IsBegin(Maze::Coordinate(1,0)),
                     " (5) Specified maze does not begin at 1, 0");

  test_print_message(passed,
                     !maze2.IsBegin(Maze::Coordinate(20,1)),
                     " (6) Specified maze does not begin at 20, 1");

  return passed;
}

std::list<Maze::MoveType> test_player(std::stringstream *mazeStream, Game::PlayerType playerType) {
  try {
    if(nullptr != mazeStream) mazeStream->seekg(0);
    Game game(mazeStream, playerType, Game::NO_PRINT);
    game.PlayUntilEnd();
    return game.GetMoves();
  }
  catch (std::string exception) {
    std::cout << exception << std::endl;
  }
  return std::list<Maze::MoveType>();
}

size_t test_random_player() {
  std::cout << "Starting Random Player Tests, these must find a solution path to receive partial credit" << std::endl
             << "NOTE: This test will hang (in an infinite loop) if you haven't implemented the RandomPlayer" << std::endl;
  std::list<Maze::MoveType> moves1_1 = test_player(nullptr, Game::RANDOM_PLAYER);
  std::list<Maze::MoveType> moves1_2 = test_player(nullptr, Game::RANDOM_PLAYER);
  std::list<Maze::MoveType> moves2_1 = test_player(&maze1, Game::RANDOM_PLAYER);
  std::list<Maze::MoveType> moves2_2 = test_player(&maze1, Game::RANDOM_PLAYER);
  std::list<Maze::MoveType> moves3_1 = test_player(&maze2, Game::RANDOM_PLAYER);
  std::list<Maze::MoveType> moves3_2 = test_player(&maze2, Game::RANDOM_PLAYER);
  if ((moves1_1.size() < 4) || (moves2_1.size() < 8) || (moves3_1.size() < 8)) {
    std::cout << "\tFAILED: Move count invalid, skipping second test" << std::endl;
    return 0;
  }

  std::cout << "\tPASSED: Partial credit for Random Player" << std::endl;

  std::cout << "Testing Solution Uniqueness" << std::endl;
  if (moves1_1 == moves1_2 && moves2_1 == moves2_2 && moves3_1 == moves3_2) {
    std::cout << "\tFAILED: Moves are not unique" << std::endl;
    return 1;
  }
  std::cout << "\tPASSED: Full credit for Random Player" << std::endl;
  return 2;
}

size_t test_efficient_player() {
  bool passed[4] = {true, true, true};

  std::cout << "Starting Efficient Player Tests, these must find the correct solution path to receive credit" << std::endl
            << "NOTE: This test will hang (in an infinite loop) if you haven't implemented the EfficientPlayer" << std::endl;

  std::list<Maze::MoveType> moves1_1 = test_player(nullptr, Game::EFFICIENT_PLAYER);
  std::list<Maze::MoveType> moves1_2 = test_player(nullptr, Game::EFFICIENT_PLAYER);

  std::cout << "Testing Default Maze" << std::endl;
  if(moves1_1 != moves1_2) {
    std::cout << "\tFAILED: Paths should match when run on the same maze" << std::endl;
    passed[0] = false;
  }
  if(moves1_1.size() != 4) {
    std::cout << "\tFAILED: Path should have 4 moves" << std::endl;
    passed[0] = false;
  }
  if(moves1_1 != std::list<Maze::MoveType>({Maze::SOUTH_MOVE, Maze::EAST_MOVE, Maze::SOUTH_MOVE, Maze::EAST_MOVE})) {
    std::cout << "\tFAILED: Path is incorrect (should be south, east, south, east)" << std::endl;
    passed[0] = false;
  }
  if (passed[0]) std::cout << "\tPassed!" << std::endl;


  std::list<Maze::MoveType> moves2_1 = test_player(&maze1, Game::EFFICIENT_PLAYER);
  std::list<Maze::MoveType> moves2_2 = test_player(&maze1, Game::EFFICIENT_PLAYER);


  std::cout << "Testing maze1" << std::endl;
  if(moves2_1 != moves2_2) {
    std::cout << "\tFAILED: Paths should match when run on the same maze" << std::endl;
    passed[1] = false;
  }
  if(moves2_1.size() != 14) {
    std::cout << "\tFAILED: Path should have 14 moves" << std::endl;
    passed[1] = false;
  }
  if(moves2_1 != std::list<Maze::MoveType>({Maze::EAST_MOVE, Maze::EAST_MOVE, Maze::EAST_MOVE, Maze::WEST_MOVE,
                                            Maze::WEST_MOVE, Maze::WEST_MOVE, Maze::SOUTH_MOVE, Maze::SOUTH_MOVE,
                                            Maze::EAST_MOVE, Maze::SOUTH_MOVE, Maze::EAST_MOVE, Maze::EAST_MOVE,
                                            Maze::NORTH_MOVE, Maze::EAST_MOVE})) {
    std::cout << "\tFAILED: Path is incorrect (should be south, east, south, east)" << std::endl;
    passed[1] = false;
  }
  if (passed[1]) std::cout << "\tPassed!" << std::endl;

  std::list<Maze::MoveType> moves3_1 = test_player(&maze2, Game::EFFICIENT_PLAYER);
  std::list<Maze::MoveType> moves3_2 = test_player(&maze2, Game::EFFICIENT_PLAYER);

  std::cout << "Testing maze2" << std::endl;
  if(moves3_1 != moves3_2) {
    std::cout << "\tFAILED: Paths should match when run on the same maze" << std::endl;
    passed[2] = false;
  }
  if(moves3_1.size() != 8) {
    std::cout << "\tFAILED: Path should have 14 moves" << std::endl;
    passed[2] = false;
  }
  if(moves3_1 != std::list<Maze::MoveType>({Maze::NORTH_MOVE, Maze::EAST_MOVE, Maze::NORTH_MOVE, Maze::EAST_MOVE,
                                            Maze::EAST_MOVE, Maze::EAST_MOVE, Maze::SOUTH_MOVE, Maze::SOUTH_MOVE})) {
    std::cout << "\tFAILED: Path is incorrect (should be north, east, north, east, east, east, south, south)" << std::endl;
    passed[2] = false;
  }
  if (passed[2]) std::cout << "\tPassed!" << std::endl;

  int mazes_passed = (size_t) passed[0] + passed[1] + passed[2];
  return mazes_passed;
}

bool test_efficient_player_exception() {
  bool passed = false;

  std::cout << "Starting Efficient Player Exception Test" << std::endl
            << "NOTE: This test will hang (in an infinite loop) if you haven't implemented the EfficientPlayer" << std::endl;

  try {
    mazeImpossible1.seekg(0);
    Game game(&mazeImpossible1, Game::EFFICIENT_PLAYER, Game::NO_PRINT);
    game.PlayUntilEnd();
  }
  catch (std::string ex) {
    passed = true;
  }
  return passed;
}

bool test_max_turns() {
  size_t num_tests_passed = 0;
  bool passed;

  std::cout << "Testing max_turns: Note: All of these tests will hand (in an infinite loop) if you don't implement the RandomPlayer. Test 4 will hang if you haven't implemented the code for this problem" << std::endl;

  std::cout << "Running Test 1" << std::endl;
  Game game2(nullptr, Game::RANDOM_PLAYER, Game::NO_PRINT);
  passed = game2.PlayUntilEnd(1000);
  if (passed == true) num_tests_passed++;
  else std::cout << "FAILED: Test 1" << std::endl;

  std::cout << "Running Test 2" << std::endl;
  maze1.seekg(0);
  Game game3(&maze1, Game::RANDOM_PLAYER, Game::NO_PRINT);
  passed = game3.PlayUntilEnd(1000);
  if (passed == true) num_tests_passed++;
  else std::cout << "FAILED: Test 2" << std::endl;

  std::cout << "Running Test 3" << std::endl;
  maze1.seekg(0);
  Game game4(&maze1, Game::RANDOM_PLAYER, Game::NO_PRINT);
  passed = game4.PlayUntilEnd(0);
  if (passed == true) num_tests_passed++;
  else std::cout << "FAILED: Test 3" << std::endl;

  std::cout << "Running Test 4" << std::endl;
  mazeImpossible2.seekg(0);
  Game game(&mazeImpossible2, Game::RANDOM_PLAYER, Game::NO_PRINT);
  passed = game.PlayUntilEnd(100);
  if (passed == false) num_tests_passed++;
  else std::cout << "FAILED: Test 4" << std::endl;

  if (num_tests_passed == 4) {
    return true;
  }
  else {
    return false;
  }
}


#endif //ECE17_SP21_FINAL_TESTING_H
