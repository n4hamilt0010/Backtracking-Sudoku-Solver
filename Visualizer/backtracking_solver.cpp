/*#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>*/

#include <cstdbool>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include "backtracking_solver.h"
#include "matrix.h"

#define DIM 9
#define BOX_DIM 3

struct coordinate{
  int row;
  int column;
};



const struct coordinate GRID_FULL = {DIM, DIM};




// coordinates_equal(coord1, coord2) returns true if the two coordinates refer to
// the same position and false otherwise

// time: O(1)
bool coordinates_equal(struct coordinate coord1, struct coordinate coord2){
  return coord1.row == coord2.row && coord1.column == coord2.column;
}



// is_valid_box(grid, box_start_row, box_start_col, num) returns true if for the
//given box (indicated by the parameters box_start_row and box_start_col)
//  within the given grid, the given number is a valid option and false otherwise

// requires: grid must not be NULL
//           box_start_row and box_start_col must be valid box starting indexes [not asserted]
//           num must be a valid number

// time: O(n^2) where n is BOX_DIM
bool is_valid_box(int grid[DIM + 1][DIM + 1], int box_start_row,
                  int box_start_col, int num){
  assert(grid);
  assert(num > 0);
  assert(num <= DIM);
  for(int i = box_start_row; i < box_start_row + BOX_DIM; ++i){
    for(int j = box_start_col; j < box_start_col + BOX_DIM; ++j){
      if(grid[i][j] == num){
        return false;
      }
    }
  }
  return true;
}



// is_valid_col(grid, col num) returns true if the given number is valid in the given column of the
// given grid and false otherwise

// requires: grid must not be NULL
//           col must be a valid column number
//           num must be a valid number

// time: O(n) where n is DIM
bool is_valid_col(int grid[DIM + 1][DIM + 1], int col, int num){
  assert(grid);
  assert(col >= 0);
  assert(col < DIM);
  assert(num > 0);
  assert(num <= DIM);
  for(int i = 0; i < DIM; ++i){
    if(grid[i][col] == num){
      return false;
    }
  }
  return true;
}



// is_valid_row(grid, row, num) returns true if the given number is valid in the given row of the
// given grid and false otherwise

// requires: grid must not be NULL
//           row must be a valid row number
//           num must be a valid number

// time: O(n) where n is DIM
bool is_valid_row(int grid[DIM + 1][DIM + 1], int row, int num){
  assert(grid);
  assert(row >= 0);
  assert(row < DIM);
  assert(num > 0);
  assert(num <= DIM);
  for(int i = 0; i < DIM; ++i){
    if(grid[row][i] == num){
      return false;
    }
  }
  return true;
}



// find_start_idx_box(idx) returns the starting row or column index of the given row or
// column index

// requires: idx must be a valid row/column index

// time: O(1)
int find_start_idx_box(int idx){
  assert(idx >= 0);
  assert(idx < DIM);
  return (idx / BOX_DIM) * BOX_DIM;
}



// is_valid(grid, row, col, num) returns true if the for the given position in
// the given grid, the given number is a valid move

// requires: grid must not be NULL
//           row and col must be valid indexes
//           num must be a valid number

// time: O(n) where n is DIM or O(m^2) where m is BOX_DIM (same number of operations)
//       since BOX_DIM^2 == DIM
bool is_valid(int grid[DIM + 1][DIM + 1], int row, int col, int num){
  assert(grid);
  assert(row >= 0);
  assert(row < DIM);
  assert(col >= 0);
  assert(col < DIM);
  assert(num > 0);
  assert(num <= DIM);
  return is_valid_row(grid, row, num) && is_valid_col(grid, col, num) &&
                                 is_valid_box(grid, find_start_idx_box(row), find_start_idx_box(col), num);
}



// get_empty_posn(grid, start_row, start_col) returns a coordinate with the row and column
// values for the next empty position to fill on the grid

// requires: grid must not be NULL
//           start_row and start_col must be valid indexes

// time: O(n^2) where n is DIM
struct coordinate get_empty_posn(int grid[DIM + 1][DIM + 1],
                                 int start_row, int start_col){
  assert(grid);
  assert(start_row >= 0);
  assert(start_row < DIM);
  assert(start_col >= 0);
  assert(start_col < DIM);
  struct coordinate retval;
  for(int row = start_row; row < DIM; ++row){
    if(row == start_row){
      for(int col = start_col; col < DIM; ++col){
        if(grid[row][col] == 0){
          retval.row = row;
          retval.column = col;
          return retval;
        }
      }
    }
    for(int col = 0; col < DIM; ++col){
      if(grid[row][col] == 0){
        retval.row = row;
        retval.column = col;
        return retval;
      }
    }
  }
  return GRID_FULL;
}



// sudoku_solver_wrapper(grid, curr_row, curr_column) returns true and solves the given
// grid if it can be solved and returns false otherwise

// effects: may mutate grid

// requires: grid must not be NULL
//           curr_row and curr_column must be valid indexes

// time: O()
bool sudoku_solver_wrapper(int grid[DIM + 1][DIM + 1], int curr_row, int curr_column){
  assert(grid);
  assert(curr_row >= 0);
  assert(curr_row < DIM);
  assert(curr_column >= 0);
  assert(curr_column < DIM);

  struct coordinate empty_posn = get_empty_posn(grid, curr_row, curr_column);

  if(coordinates_equal(empty_posn, GRID_FULL)){
    return true;
  }

  const int row = empty_posn.row;
  const int col = empty_posn.column;
  for(int num = 1; num <= DIM; ++num){
    if(is_valid(grid, row, col, num)){
      grid[row][col] = num;
      if(sudoku_solver_wrapper(grid, row, col)){
        return true;
      }
      grid[row][col] = 0;
    }
  }
  return false;
}



// sudoku_solver(grid) returns true and solves the given grid if it can be solved and returns
// false otherwise

// effects: may mutate grid

// requires: grid must not be NULL, and grid must be incomplete

// time: O()
bool sudoku_solver(int grid[DIM + 1][DIM + 1]){
  assert(grid);
  return sudoku_solver_wrapper(grid, 0, 0);
}
