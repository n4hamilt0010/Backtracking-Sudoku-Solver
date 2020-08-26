#ifndef BACKTRACKING_SOLVER_H
#define BACKTRACKING_SOLVER_H

struct coordinate;
// coordinates_equal(coord1, coord2) returns true if the two coordinates refer to
// the same position and false otherwise

// time: O(1)
bool coordinates_equal(struct coordinate coord1, struct coordinate coord2);



// is_valid_box(grid, box_start_row, box_start_col, num) returns true if for the
//given box (indicated by the parameters box_start_row and box_start_col)
//  within the given grid, the given number is a valid option and false otherwise

// requires: grid must not be NULL
//           box_start_row and box_start_col must be valid box starting indexes [not asserted]
//           num must be a valid number

// time: O(n^2) where n is BOX_DIM
bool is_valid_box(int grid[][10], int box_start_row, int box_start_col, int num);



// is_valid_col(grid, col num) returns true if the given number is valid in the given column of the
// given grid and false otherwise

// requires: grid must not be NULL
//           col must be a valid column number
//           num must be a valid number

// time: O(n) where n is DIM
bool is_valid_col(int grid[][10], int col, int num);



// is_valid_row(grid, row, num) returns true if the given number is valid in the given row of the
// given grid and false otherwise

// requires: grid must not be NULL
//           row must be a valid row number
//           num must be a valid number

// time: O(n) where n is DIM
bool is_valid_row(int grid[][10], int row, int num);


// find_start_idx_box(idx) returns the starting row or column index of the given row or
// column index

// requires: idx must be a valid row/column index

// time: O(1)
int find_start_idx_box(int idx);



// is_valid(grid, row, col, num) returns true if the for the given position in
// the given grid, the given number is a valid move

// requires: grid must not be NULL
//           row and col must be valid indexes
//           num must be a valid number

// time: O(n) where n is DIM or O(m^2) where m is BOX_DIM (same number of operations)
//       since BOX_DIM^2 == DIM
bool is_valid(int grid[][10], int row, int col, int num);



// get_empty_posn(grid, start_row, start_col) returns a coordinate with the row and column
// values for the next empty position to fill on the grid

// requires: grid must not be NULL
//           start_row and start_col must be valid indexes

// time: O(n^2) where n is DIM
struct coordinate get_empty_posn(int grid[][10], int start_row, int start_col);



// sudoku_solver_wrapper(grid, curr_row, curr_column) returns true and solves the given
// grid if it can be solved and returns false otherwise

// effects: may mutate grid

// requires: grid must not be NULL
//           curr_row and curr_column must be valid indexes

// time: O()
bool sudoku_solver_wrapper(int grid[][10], int curr_row, int curr_column);



// sudoku_solver(grid) returns true and solves the given grid if it can be solved and returns
// false otherwise

// effects: may mutate grid

// requires: grid must not be NULL, and grid must be incomplete

// time: O()
bool sudoku_solver(int grid[][10]);


#endif // BACKTRACKING_SOLVER_H
