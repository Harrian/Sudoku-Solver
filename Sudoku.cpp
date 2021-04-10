/* file Sudoku.h */

#include "Sudoku.h"
#include "ArrayUtil.h"
#include <iostream>
#include <ostream>

Solver::Solver(const SudokuBoard & original_state, std::size_t start_point) : original_state(original_state), current_state(original_state), start_point(start_point)
{
}

void Solver::solve(void)
{
  std::size_t current_point = start_point;
  while(!Sudoku::isComplete(current_state))
  {
    const SudokuBoard::size_type ypos = Sudoku::ypos(current_point);
    const SudokuBoard::value_type::size_type xpos = Sudoku::xpos(current_point);
    if(original_state[ypos][xpos] == 0)
    {
      if(current_state[ypos][xpos] == 9)
      {
        current_state[ypos][xpos] = 0;
        current_point--;
      }
      else
      {
        current_state[ypos][xpos]++;
        if(Sudoku::isPossibleSolution(current_state))
        {
          current_point++;
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
  std::array<std::array<bool, sudoku_dimensions>, sudoku_dimensions> column_flags = init_array<std::array<bool, sudoku_dimensions>, sudoku_dimensions>(init_array<bool, sudoku_dimensions>(false));

  for(SudokuBoard::size_type i = 0; i < sudoku_dimensions; i++)
  {
    std::array<bool, sudoku_dimensions> row_flags = init_array<bool, sudoku_dimensions>(false);
    for(SudokuBoard::value_type::size_type j = 0; j < sudoku_dimensions; j++)
    {
      if(board[i][j] == 0 || row_flags[board[i][j]-1] || column_flags[j][board[i][j]-1])
      {
        return false;
      }

      row_flags[board[i][j]-1] = true;
      column_flags[j][board[i][j]-1] = true;
    }
  }

  // currently only works for 9 by 9 sudoku math was eluding me without a white board.
  std::array<std::array<SudokuElementType, sudoku_dimensions>, sudoku_dimensions> squares{
    std::array<SudokuElementType, sudoku_dimensions>{
      board[0][0],board[0][1],board[0][2],
      board[1][0],board[1][1],board[1][2],
      board[2][0],board[2][1],board[2][2]
    },
    std::array<SudokuElementType, sudoku_dimensions>{
      board[0][3],board[0][4],board[0][5],
      board[1][3],board[1][4],board[1][5],
      board[2][3],board[2][4],board[2][5]
    },
    std::array<SudokuElementType, sudoku_dimensions>{
      board[0][6],board[0][7],board[0][8],
      board[1][6],board[1][7],board[1][8],
      board[2][6],board[2][7],board[2][8]
    },
    std::array<SudokuElementType, sudoku_dimensions>{
      board[3][0],board[3][1],board[3][2],
      board[4][0],board[4][1],board[4][2],
      board[5][0],board[5][1],board[5][2]
    },
    std::array<SudokuElementType, sudoku_dimensions>{
      board[3][3],board[3][4],board[3][5],
      board[4][3],board[4][4],board[4][5],
      board[5][3],board[5][4],board[5][5]
    },
    std::array<SudokuElementType, sudoku_dimensions>{
      board[3][6],board[3][7],board[3][8],
      board[4][6],board[4][7],board[4][8],
      board[5][6],board[5][7],board[5][8]
    },
    std::array<SudokuElementType, sudoku_dimensions>{
      board[6][0],board[6][1],board[6][2],
      board[7][0],board[7][1],board[7][2],
      board[8][0],board[8][1],board[8][2]
    },
    std::array<SudokuElementType, sudoku_dimensions>{
      board[6][3],board[6][4],board[6][5],
      board[7][3],board[7][4],board[7][5],
      board[8][3],board[8][4],board[8][5]
    },
    std::array<SudokuElementType, sudoku_dimensions>{
      board[6][6],board[6][7],board[6][8],
      board[7][6],board[7][7],board[7][8],
      board[8][6],board[8][7],board[8][8]
    }
  };

  for(const SudokuBoard::value_type & square: squares)
  {
    std::array<bool, sudoku_dimensions> flags = init_array<bool, sudoku_dimensions>(false);
    for(const SudokuBoard::value_type::value_type value: square)
    {
      if(flags[value-1])
      {
        return false;
      }

      flags[value-1] = true;
    }
  }

  return true;
}

bool Sudoku::isPossibleSolution(const SudokuBoard & board)
{
  std::array<std::array<bool, sudoku_dimensions>, sudoku_dimensions> column_flags = init_array<std::array<bool, sudoku_dimensions>, sudoku_dimensions>(init_array<bool, sudoku_dimensions>(false));

  for(SudokuBoard::size_type i = 0; i < sudoku_dimensions; i++)
  {
    std::array<bool, sudoku_dimensions> row_flags = init_array<bool, sudoku_dimensions>(false);
    for(SudokuBoard::value_type::size_type j = 0; j < sudoku_dimensions; j++)
    {
      if(board[i][j] != 0)
      {
        if(row_flags[board[i][j]-1] || column_flags[j][board[i][j]-1])
        {
          return false;
        }

        row_flags[board[i][j]-1] = true;
        column_flags[j][board[i][j]-1] = true;
      }
    }
  }

  // currently only works for 9 by 9 sudoku math was eluding me without a white board.
  std::array<std::array<SudokuElementType, sudoku_dimensions>, sudoku_dimensions> squares{
    std::array<SudokuElementType, sudoku_dimensions>{
      board[0][0],board[0][1],board[0][2],
      board[1][0],board[1][1],board[1][2],
      board[2][0],board[2][1],board[2][2]
    },
    std::array<SudokuElementType, sudoku_dimensions>{
      board[0][3],board[0][4],board[0][5],
      board[1][3],board[1][4],board[1][5],
      board[2][3],board[2][4],board[2][5]
    },
    std::array<SudokuElementType, sudoku_dimensions>{
      board[0][6],board[0][7],board[0][8],
      board[1][6],board[1][7],board[1][8],
      board[2][6],board[2][7],board[2][8]
    },
    std::array<SudokuElementType, sudoku_dimensions>{
      board[3][0],board[3][1],board[3][2],
      board[4][0],board[4][1],board[4][2],
      board[5][0],board[5][1],board[5][2]
    },
    std::array<SudokuElementType, sudoku_dimensions>{
      board[3][3],board[3][4],board[3][5],
      board[4][3],board[4][4],board[4][5],
      board[5][3],board[5][4],board[5][5]
    },
    std::array<SudokuElementType, sudoku_dimensions>{
      board[3][6],board[3][7],board[3][8],
      board[4][6],board[4][7],board[4][8],
      board[5][6],board[5][7],board[5][8]
    },
    std::array<SudokuElementType, sudoku_dimensions>{
      board[6][0],board[6][1],board[6][2],
      board[7][0],board[7][1],board[7][2],
      board[8][0],board[8][1],board[8][2]
    },
    std::array<SudokuElementType, sudoku_dimensions>{
      board[6][3],board[6][4],board[6][5],
      board[7][3],board[7][4],board[7][5],
      board[8][3],board[8][4],board[8][5]
    },
    std::array<SudokuElementType, sudoku_dimensions>{
      board[6][6],board[6][7],board[6][8],
      board[7][6],board[7][7],board[7][8],
      board[8][6],board[8][7],board[8][8]
    }
  };

  for(const SudokuBoard::value_type & square: squares)
  {
    std::array<bool, sudoku_dimensions> flags = init_array<bool, sudoku_dimensions>(false);
    for(const SudokuBoard::value_type::value_type value: square)
    {
      if(value != 0)
      {
        if(flags[value-1])
        {
          return false;
        }

        flags[value-1] = true;
      }
    }
  }

  return true;
}
