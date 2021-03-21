/* file SudokuParser.cpp */

#include "SudokuParser.h"

#include "Sudoku.h"

#include <string>
#include <stdexcept>
#include <fstream>

SudokuBoard board_from_file(std::ifstream & file)
{
  SudokuBoard ret;

  std::string line;
  SudokuBoard::size_type current_line = 0;

  while(std::getline(file, line))
  {
    const std::string const_line(line);
    if(const_line.size() != 9)
    {
      throw std::runtime_error("Not exactly 9 chars on sudoku line");
    }

    SudokuBoard::value_type::size_type current_position = 0;
    while(current_position < 9 && current_position < const_line.size())
    {
      if((const_line[current_position] < '1' || const_line[current_position] > '9') && const_line[current_position] != '_')
      {
        throw std::runtime_error("invalid character in sudoku line");
      }
      ret[current_line][current_position] = const_line[current_position] != '_' ? const_line[current_position] - '0' : 0;
      current_position++;
    }
    current_line++;
  }

  if(current_line != 9)
  {
    throw std::runtime_error("Not exactly 9 lines on sudoku file");
  }

  return ret;
}
