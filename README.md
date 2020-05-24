//# Backtracking-Sudoku-Solver
//Sudoku solver using a backtracking algorithm

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#define DIM 16
#define BOX_DIM 4

struct coordinate{
  int row;
  int column;
};



const struct coordinate GRID_FULL = {DIM, DIM};



// print_line() prints out the top and bottom lines for the grid

// effects: produces output

// time: O(n) 
void print_line(void){
  const int num_iterations = (3 * DIM) + DIM + 1;
  for(int i = 0; i < num_iterations; ++i){
    printf("-");
  }
  printf("\n");
}



// print_grid(grid) prints out the current state of the given grid

// effects: produces output

// requires: grid must not be NULL

// time: O(n^3) where n is DIM
void print_grid(int grid[DIM][DIM]){
  print_line();
  
  for(int row = 0; row < DIM; ++row){
    printf("|");
    for(int col = 0; col < DIM; ++col){
      if(grid[row][col] == 0){
        printf("   |");
      } else{
        printf(" %d |", grid[row][col]);
      }
    }
    printf("\n");
    print_line();
  }
}



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
bool is_valid_box(int grid[DIM][DIM], int box_start_row, 
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
bool is_valid_col(int grid[DIM][DIM], int col, int num){
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
bool is_valid_row(int grid[DIM][DIM], int row, int num){
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
bool is_valid(int grid[DIM][DIM], int row, int col, int num){
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
struct coordinate get_empty_posn(int grid[DIM][DIM], 
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
bool sudoku_solver_wrapper(int grid[DIM][DIM], int curr_row, int curr_column){
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
bool sudoku_solver(int grid[DIM][DIM]){
  assert(grid);
  return sudoku_solver_wrapper(grid, 0, 0);
}



int main(){
  int sudoku_grid[DIM][DIM] = {
    {0,11,9,0,0,16,13,4,0,0,14,0,10,6,15,0},
    {4,12,15,0,3,6,0,11,0,5,0,1,16,7,14,2},
    {1,0,6,0,15,2,0,0,11,9,10,0,0,0,8,0},
    {0,13,0,0,0,1,0,0,4,6,0,15,0,0,0,0},
    {0,0,0,0,0,0,15,0,8,1,5,3,0,4,11,7},
    {6,0,1,0,0,12,8,0,9,0,0,2,0,0,3,0},
    {14,0,4,13,6,0,0,3,0,12,7,10,8,0,2,0},
    {3,8,0,0,4,7,2,0,6,0,0,0,0,12,16,5},
    {13,0,0,16,0,8,14,10,3,4,15,0,12,5,1,11},
    {0,0,0,6,2,0,0,1,10,0,11,0,15,3,0,9},
    {7,0,0,12,0,4,0,15,5,0,9,14,0,0,0,0},
    {10,0,0,8,0,0,11,0,0,0,1,12,4,0,13,16},
    {0,0,0,0,0,0,7,0,15,2,0,0,0,0,12,3},
    {0,0,7,0,0,10,6,0,1,8,0,13,11,0,9,14},
    {8,6,5,0,0,3,0,0,14,0,0,9,0,0,0,0},
    {0,16,0,2,0,0,0,14,0,10,0,0,0,0,0,0}};
  print_grid(sudoku_grid);
  printf("\n");
  if(sudoku_solver(sudoku_grid)){
    print_grid(sudoku_grid);
  } else{
    printf("Error, sudoku_solver failed\n");
  }
}



/*int sudoku_grid[DIM][DIM] = {{0,0,2,9,8,0,5,0,0},
                         {4,0,0,0,7,0,0,1,3},
                         {0,3,9,6,0,4,0,7,0},
                         {2,0,0,0,5,6,4,0,0},
                         {8,4,0,3,0,0,2,0,1},
                         {9,0,7,0,0,1,0,8,6},
                         {6,0,0,7,0,5,1,3,0},
                         {0,9,1,4,0,0,0,0,5},
                         {0,2,0,0,3,0,6,0,8}};*/
