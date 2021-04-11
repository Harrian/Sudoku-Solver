/* file Sudoku.h */

#include "Sudoku.h"
#include "ArrayUtil.h"
#include <iostream>
#include <ostream>

static inline SudokuBoard::value_type::size_type calculate_square_index(SudokuElementType row, SudokuElementType column)
{
  return row + (column / sudoku_inner_square_dimensions) - (row % sudoku_inner_square_dimensions);
}

Solver::Solver(const SudokuBoard & original_state, std::size_t start_point) : original_state(original_state), current_state(original_state), start_point(start_point)
{
}

void Solver::solve(void)
{
  std::size_t current_point = start_point;
  bool is_possibly_complete = true;
  int_fast8_t blanks = Sudoku::getNumBlanks(current_state);
  while(!(is_possibly_complete && blanks == 0 && Sudoku::isComplete(current_state)))
  {
    const SudokuBoard::size_type ypos = Sudoku::ypos(current_point);
    const SudokuBoard::value_type::size_type xpos = Sudoku::xpos(current_point);
    if(original_state[ypos][xpos] == 0)
    {
      if(current_state[ypos][xpos] == 9)
      {
        current_state[ypos][xpos] = 0;
        current_point--;
        while(original_state[Sudoku::ypos(current_point)][Sudoku::xpos(current_point)] != 0)
          current_point--;
        blanks++;
      }
      else
      {
        if(current_state[ypos][xpos] == 0)
          blanks--;
        current_state[ypos][xpos]++;
        if(Sudoku::isPossibleSolution(current_state))
        {
          is_possibly_complete = true;
          current_point++;
        }
        else
        {
          is_possibly_complete = false;
        }
      }
    }
    else
    {
      current_point++;
    }
  }
}

void Solver::printCurrentState(std::ostream & stream)
{
  for(const SudokuBoard::value_type x: current_state)
  {
    for(const SudokuBoard::value_type::value_type y: x)
      stream << (y == 0 ? '_' : static_cast<char>(y + '0'));
    stream << std::endl;
  }
}

SudokuBoard::size_type Sudoku::ypos(std::size_t pos)
{
  return (pos / sudoku_dimensions) % sudoku_dimensions;
}

SudokuBoard::value_type::size_type Sudoku::xpos(std::size_t pos)
{
  return pos % sudoku_dimensions;
}

bool Sudoku::isComplete(const SudokuBoard & board)
{
  std::array<bool, sudoku_dimensions * sudoku_dimensions> column_flags = init_array<bool, sudoku_dimensions * sudoku_dimensions>(false);
  std::array<bool, sudoku_dimensions * sudoku_dimensions> row_flags = init_array<bool, sudoku_dimensions * sudoku_dimensions>(false);
  std::array<bool, sudoku_dimensions * sudoku_dimensions> square_flags = init_array<bool, sudoku_dimensions * sudoku_dimensions>(false);

  for(SudokuBoard::size_type i = 0; i < sudoku_dimensions; i++)
  {
    for(SudokuBoard::value_type::size_type j = 0; j < sudoku_dimensions; j++)
    {
        if(board[i][j] == 0 || row_flags[i * sudoku_dimensions + board[i][j]-1] || column_flags[j * sudoku_dimensions + board[i][j]-1] || square_flags[calculate_square_index(i,j) * sudoku_dimensions + board[i][j]-1])
        {
          return false;
        }

        row_flags[i * sudoku_dimensions + board[i][j]-1] = true;
        column_flags[j * sudoku_dimensions + board[i][j]-1] = true;
        square_flags[calculate_square_index(i,j) * sudoku_dimensions + board[i][j]-1] = true;
    }
  }

  return true;
}

bool Sudoku::isPossibleSolution(const SudokuBoard & board)
{
  std::array<bool, sudoku_dimensions * sudoku_dimensions> column_flags = init_array<bool, sudoku_dimensions * sudoku_dimensions>(false);
  std::array<bool, sudoku_dimensions * sudoku_dimensions> row_flags = init_array<bool, sudoku_dimensions * sudoku_dimensions>(false);
  std::array<bool, sudoku_dimensions * sudoku_dimensions> square_flags = init_array<bool, sudoku_dimensions * sudoku_dimensions>(false);

  for(SudokuBoard::size_type i = 0; i < sudoku_dimensions; i++)
  {
    for(SudokuBoard::value_type::size_type j = 0; j < sudoku_dimensions; j++)
    {
      if(board[i][j] != 0)
      {
        if(row_flags[i * sudoku_dimensions + board[i][j]-1] || column_flags[j * sudoku_dimensions + board[i][j]-1] || square_flags[calculate_square_index(i,j) * sudoku_dimensions + board[i][j]-1])
        {
          return false;
        }

        row_flags[i * sudoku_dimensions + board[i][j]-1] = true;
        column_flags[j * sudoku_dimensions + board[i][j]-1] = true;
        square_flags[calculate_square_index(i,j) * sudoku_dimensions + board[i][j]-1] = true;
      }
    }
  }

  return true;
}

int_fast8_t Sudoku::getNumBlanks(const SudokuBoard & board)
{
  int_fast8_t ret = 0;
  for(const auto & x: board)
  {
    for(const auto & y: x)
    {
      if(y == 0)
      {
        ret++;
      }
    }
  }
  return ret;
}
