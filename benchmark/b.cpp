#include <benchmark/benchmark.h>
#include "Sudoku.h"

#include <vector>
#include <random>

static void randomize_board(SudokuBoard & to_randomize)
{
  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<> distrib(0, 9);

  for(auto & x: to_randomize)
    for(auto & y: x)
      y = distrib(gen);
}

static int random_number_to_remove(void)
{
  static thread_local std::random_device rd;  //Will be used to obtain a seed for the random number engine
  static thread_local std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  static thread_local std::uniform_int_distribution<> distrib(0, sudoku_dimensions * sudoku_dimensions - 1 - 17);
  return distrib(gen);
}

static void randomly_remove(SudokuBoard & to_randomize)
{
  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<> distrib(0, sudoku_dimensions * sudoku_dimensions - 1);

  int num_to_remove = random_number_to_remove();

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
  for(auto _ : state)
  {
    randomize_board(board);
    benchmark::DoNotOptimize(Sudoku::isPossibleSolution(board));
  }
}

BENCHMARK(BM_Sudoku_Is_Possible_Solution);

static void BM_Sudoku_Is_Complete_Solution(benchmark::State & state)
{
  SudokuBoard board;
  for(auto _ : state)
  {
    randomize_board(board);
    benchmark::DoNotOptimize(Sudoku::isComplete(board));
  }
}

BENCHMARK(BM_Sudoku_Is_Complete_Solution);

static void BM_Sudoku_Solver(benchmark::State & state)
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
  for(auto _ : state)
  {
    SudokuBoard copy = board;
    randomly_remove(copy);
    Solver solver(copy);
    solver.solve();
    benchmark::ClobberMemory();
  }
}

BENCHMARK(BM_Sudoku_Solver);

BENCHMARK_MAIN();
