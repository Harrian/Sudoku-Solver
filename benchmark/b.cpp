#include <benchmark/benchmark.h>
#include "Sudoku.h"

#include <vector>
#include <random>
#include <iostream>

static void randomize_board(SudokuBoard & to_randomize, std::mt19937 & gen, std::uniform_int_distribution<> & distrib)
{
  //static thread_local std::mt19937 gen(0); //Standard mersenne_twister_engine seeded with rd()
  //static thread_local std::uniform_int_distribution<> distrib(0, 9);

  for(auto & x: to_randomize)
    for(auto & y: x)
      y = distrib(gen);
}

static int random_number_to_remove(std::mt19937 & gen, std::uniform_int_distribution<> & distrib)
{
  //static thread_local std::mt19937 gen(2); //Standard mersenne_twister_engine seeded with rd()
  //static thread_local std::uniform_int_distribution<> distrib(0, sudoku_dimensions * sudoku_dimensions - 1 - 17);
  return distrib(gen);
}

static void randomly_remove(SudokuBoard & to_randomize, std::mt19937 & gen, std::uniform_int_distribution<> & distrib, std::mt19937 & gen_to_remove, std::uniform_int_distribution<> & distrib_to_remove)
{
  //static thread_local std::mt19937 gen(1); //Standard mersenne_twister_engine seeded with rd()
  //static thread_local std::uniform_int_distribution<> distrib(0, sudoku_dimensions * sudoku_dimensions - 1);

  int num_to_remove = random_number_to_remove(gen_to_remove, distrib_to_remove);

  for(int i = 0; i < num_to_remove; i++)
  {
    int to_remove = distrib(gen);
    const SudokuBoard::size_type ypos = Sudoku::ypos(to_remove);
    const SudokuBoard::value_type::size_type xpos = Sudoku::xpos(to_remove);
    to_randomize[ypos][xpos] = 0;
  }
}

static void BM_Sudoku_Is_Possible_Solution(benchmark::State & state)
{
  SudokuBoard board;
  static thread_local std::mt19937 gen(0); //Standard mersenne_twister_engine seeded with rd()
  static thread_local std::uniform_int_distribution<> distrib(0, 9);
  for(auto _ : state)
  {
    randomize_board(board, gen, distrib);
    benchmark::DoNotOptimize(Sudoku::isPossibleSolution(board));
  }
}

BENCHMARK(BM_Sudoku_Is_Possible_Solution);

static void BM_Sudoku_Is_Complete_Solution(benchmark::State & state)
{
  SudokuBoard board;
  static thread_local std::mt19937 gen(0); //Standard mersenne_twister_engine seeded with rd()
  static thread_local std::uniform_int_distribution<> distrib(0, 9);
  for(auto _ : state)
  {
    randomize_board(board, gen, distrib);
    benchmark::DoNotOptimize(Sudoku::isComplete(board));
  }
}

BENCHMARK(BM_Sudoku_Is_Complete_Solution);

static void printCurrentState(const SudokuBoard & current_state, std::ostream & stream)
{
  stream << std::endl;
  for(const SudokuBoard::value_type x: current_state)
  {
    for(const SudokuBoard::value_type::value_type y: x)
      stream << (y == 0 ? '_' : static_cast<char>(y + '0'));
    stream << std::endl;
  }
  stream << std::endl;
}

static void BM_Sudoku_Solver_Board1(benchmark::State & state)
{
  const SudokuBoard board = {
    std::array<SudokuElementType, 9>{8,2,7,1,5,4,3,9,6},
    std::array<SudokuElementType, 9>{9,6,5,3,2,7,1,4,8},
    std::array<SudokuElementType, 9>{3,4,1,6,8,9,7,5,2},
    std::array<SudokuElementType, 9>{5,9,3,4,6,8,2,7,1},
    std::array<SudokuElementType, 9>{4,7,2,5,1,3,6,8,9},
    std::array<SudokuElementType, 9>{6,1,8,9,7,2,4,3,5},
    std::array<SudokuElementType, 9>{7,8,6,2,3,5,9,1,4},
    std::array<SudokuElementType, 9>{1,5,4,7,9,6,8,2,3},
    std::array<SudokuElementType, 9>{2,3,9,8,4,1,5,6,7}};
  static thread_local std::mt19937 gen(2);
  static thread_local std::uniform_int_distribution<> distrib(0, sudoku_dimensions * sudoku_dimensions - 1);
  static thread_local std::mt19937 gen_to_remove(2); //Standard mersenne_twister_engine seeded with rd()
  static thread_local std::uniform_int_distribution<> distrib_to_remove(0, sudoku_dimensions * sudoku_dimensions - 1 - 17);
  for(auto _ : state)
  {
    SudokuBoard copy = board;
    randomly_remove(copy, gen, distrib, gen_to_remove, distrib_to_remove);
    Solver solver(copy);
    solver.solve();
    benchmark::ClobberMemory();
  }
}

BENCHMARK(BM_Sudoku_Solver_Board1);

static void BM_Sudoku_Solver_Board2(benchmark::State & state)
{
  const SudokuBoard board = {
    std::array<SudokuElementType, 9>{3,1,5,9,8,7,4,6,2},
    std::array<SudokuElementType, 9>{4,9,2,6,3,1,5,7,8},
    std::array<SudokuElementType, 9>{7,8,6,4,5,2,3,9,1},
    std::array<SudokuElementType, 9>{8,4,9,1,7,3,6,2,5},
    std::array<SudokuElementType, 9>{1,5,3,2,6,9,7,8,4},
    std::array<SudokuElementType, 9>{2,6,7,5,4,8,9,1,3},
    std::array<SudokuElementType, 9>{5,2,1,7,9,4,8,3,6},
    std::array<SudokuElementType, 9>{9,3,4,8,1,6,2,5,7},
    std::array<SudokuElementType, 9>{6,7,8,3,2,5,1,4,9}};
  static thread_local std::mt19937 gen(2);
  static thread_local std::uniform_int_distribution<> distrib(0, sudoku_dimensions * sudoku_dimensions - 1);
  static thread_local std::mt19937 gen_to_remove(2); //Standard mersenne_twister_engine seeded with rd()
  static thread_local std::uniform_int_distribution<> distrib_to_remove(0, sudoku_dimensions * sudoku_dimensions - 1 - 17);
  for(auto _ : state)
  {
    SudokuBoard copy = board;
    randomly_remove(copy, gen, distrib, gen_to_remove, distrib_to_remove);
    Solver solver(copy);
    solver.solve();
    benchmark::ClobberMemory();
  }
}

BENCHMARK(BM_Sudoku_Solver_Board2);

static void BM_Sudoku_Solver_Board3(benchmark::State & state)
{
  const SudokuBoard board = {
    std::array<SudokuElementType, 9>{9,8,7,6,5,4,3,2,1},
    std::array<SudokuElementType, 9>{2,4,6,1,7,3,9,8,5},
    std::array<SudokuElementType, 9>{3,5,1,9,2,8,7,4,6},
    std::array<SudokuElementType, 9>{1,2,8,5,3,7,6,9,4},
    std::array<SudokuElementType, 9>{6,3,4,8,9,2,1,5,7},
    std::array<SudokuElementType, 9>{7,9,5,4,6,1,8,3,2},
    std::array<SudokuElementType, 9>{5,1,9,2,8,6,4,7,3},
    std::array<SudokuElementType, 9>{4,7,2,3,1,9,5,6,8},
    std::array<SudokuElementType, 9>{8,6,3,7,4,5,2,1,9}};
  static thread_local std::mt19937 gen(2);
  static thread_local std::uniform_int_distribution<> distrib(0, sudoku_dimensions * sudoku_dimensions - 1);
  static thread_local std::mt19937 gen_to_remove(2); //Standard mersenne_twister_engine seeded with rd()
  static thread_local std::uniform_int_distribution<> distrib_to_remove(0, sudoku_dimensions * sudoku_dimensions - 1 - 17);
  for(auto _ : state)
  {
    SudokuBoard copy = board;
    randomly_remove(copy, gen, distrib, gen_to_remove, distrib_to_remove);
    Solver solver(copy);
    solver.solve();
    benchmark::ClobberMemory();
  }
}

BENCHMARK(BM_Sudoku_Solver_Board3);

static void BM_Sudoku_Solver_Board4(benchmark::State & state)
{
  const SudokuBoard board = {
    std::array<SudokuElementType, 9>{9,6,2,4,1,5,3,7,8},
    std::array<SudokuElementType, 9>{3,7,4,9,2,8,5,6,1},
    std::array<SudokuElementType, 9>{1,8,5,7,6,3,4,2,9},
    std::array<SudokuElementType, 9>{7,5,3,2,8,4,1,9,6},
    std::array<SudokuElementType, 9>{2,1,8,3,9,6,7,4,5},
    std::array<SudokuElementType, 9>{4,9,6,1,5,7,8,3,2},
    std::array<SudokuElementType, 9>{5,3,1,6,7,2,9,8,4},
    std::array<SudokuElementType, 9>{6,4,9,8,3,1,2,5,7},
    std::array<SudokuElementType, 9>{8,2,7,5,4,9,6,1,3}};
  static thread_local std::mt19937 gen(2);
  static thread_local std::uniform_int_distribution<> distrib(0, sudoku_dimensions * sudoku_dimensions - 1);
  static thread_local std::mt19937 gen_to_remove(2); //Standard mersenne_twister_engine seeded with rd()
  static thread_local std::uniform_int_distribution<> distrib_to_remove(0, sudoku_dimensions * sudoku_dimensions - 1 - 17);
  for(auto _ : state)
  {
    SudokuBoard copy = board;
    randomly_remove(copy, gen, distrib, gen_to_remove, distrib_to_remove);
    Solver solver(copy);
    solver.solve();
    benchmark::ClobberMemory();
  }
}

BENCHMARK(BM_Sudoku_Solver_Board4);

BENCHMARK_MAIN();
