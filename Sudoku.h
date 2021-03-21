/* file Sudoku.h */

#ifndef SUDOKU_H
#define SUDOKU_H

#include <array>
#include <cstdint>
#include <ostream>

using SudokuElementType = int_fast8_t;
constexpr SudokuElementType sudoku_dimensions = 9;
constexpr SudokuElementType sudoku_inner_square_dimensions = 3;
static_assert(sudoku_dimensions % sudoku_inner_square_dimensions == 0, "Error squares cannot be even with given inner square dimensions");
using SudokuBoard = std::array<std::array<SudokuElementType, sudoku_dimensions>, sudoku_dimensions>;
using ConstSudokuBoard = const std::array<const std::array<SudokuElementType, sudoku_dimensions>, sudoku_dimensions>;

namespace Sudoku
{
  // 0,0 is upper left most corner of sudoku board
  // Y,X
  SudokuBoard::size_type ypos(std::size_t);
  SudokuBoard::value_type::size_type xpos(std::size_t);

  bool isPossibleSolution(const SudokuBoard & board);
  bool isComplete(const SudokuBoard & board);
}

class Solver
{
  private:
    ConstSudokuBoard original_state;
    SudokuBoard current_state;
    const std::size_t start_point;

  public:
    Solver(ConstSudokuBoard original_state, std::size_t start_point = 0);
    void solve(void);
    void printCurrentState(std::ostream & stream);
    SudokuBoard getCurrentState(void)
    {
      return current_state;
    }
};

#endif /* SUDOKU_H */
