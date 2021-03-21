/* file SudokuParser.h */

#ifndef SUDOKUPARSER_H
#define SUDOKUPARSER_H

#include "Sudoku.h"
#include <fstream>

SudokuBoard board_from_file(std::ifstream & file);

#endif /* SUDOKUPARSER_H */
