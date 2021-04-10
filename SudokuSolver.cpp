/* file SudokuSolver.cpp */

#include "Sudoku.h"
#include "SudokuParser.h"

#include <iostream>
#include <fstream>
#include <stdexcept>

namespace
{
  void dump_usage(const char * const progam_name, std::ostream & stream);
}


int main(int argc, char** argv)
{
  const char * const program_name = *argv;
  if(argc != 2)
  {
    dump_usage(program_name, std::cerr);
    return 1;
  }

  unsigned int positional_arguments_counter = 0;
  unsigned int sudoku_file_index = 0;

  for(int i = 1; i < argc; i++)
  {
    if(positional_arguments_counter > 0)
    {
      std::cerr << "Error: too many positional arguments passed" << std::endl;
      dump_usage(program_name, std::cerr);
      return 1;
    }
    else if(positional_arguments_counter == 0)
    {
      positional_arguments_counter++;
      sudoku_file_index = i;
    }
  }

  if(positional_arguments_counter != 1)
  {
    dump_usage(program_name, std::cerr);
    return 1;
  }

  try
  {
    const SudokuBoard original_board = [](const char * const file_name) -> SudokuBoard
      {
        std::ifstream sudoku_file(file_name);

        if(sudoku_file)
        {
          SudokuBoard parsed_board = board_from_file(sudoku_file);
          return parsed_board;
        }
        else
        {
          throw std::runtime_error("Couldn't read file");
        }
      }(argv[sudoku_file_index]);

    Solver solver(original_board);
    solver.solve();
    solver.printCurrentState(std::cout);
  }
  catch (const std::runtime_error & e)
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  return 0;
}

namespace
{
  void dump_usage(const char * const progam_name, std::ostream & stream)
  {
    stream << "Usage: "
           << progam_name
           << " "
           << "SUDOKUFILE"
           << std::endl
           << std::endl;

    stream << "SUDOKUFILE     should be a file that is formatted like:" << std::endl
           << "               3___8____" << std::endl
           << "               ______57_" << std::endl
           << "               __6__23_1" << std::endl
           << "               _4___36__" << std::endl
           << "               1_3___7_4" << std::endl
           << "               __75___1_" << std::endl
           << "               5_17__8__" << std::endl
           << "               _34______" << std::endl
           << "               ____2___9" << std::endl;
  }
}
