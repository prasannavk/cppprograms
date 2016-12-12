#include <iostream>
#include <vector>

// Converting an eight queens solution for practice.

using namespace std;

int GRID_SIZE = 8;

bool CheckValid(vector<int> columns, int row1, int column1);

void PlaceQueens(int row, vector<int> columns, vector<vector<int>> &results) {
  if (row == GRID_SIZE) { // Found a valid placement
    results.push_back(columns);
  } else {
    for (int col = 0; col < 8; col++) {
      if (CheckValid(columns, row, col)) {
        columns[row] = col;  // Place queen
        PlaceQueens(row + 1, columns, results);
      }
    }
  }
}

// Check if (row1, column1) is a valid spot for a queen by checking if there is
// a queen in the same column or diagonal. We don't need to check it for queens
// in the same row because the calling PlaceQueens only attempts to place one
// queen at a time. We know this row is empty.
bool CheckValid(vector<int> columns, int row1, int column1) {
  for (int row2 = 0; row2 < row1; ++row2) {
    int column2 = columns[row2];
    if (column2 == column1) {
      return false;
    }

    // Check the diagonals: if the distance between the columns equals the
    // distance between the rows, then they're in the same diagonal.
    int column_distance = abs(column2 - column1);

    // row1 > row2, so no need for abs
    int row_distance = row1 - row2;
    if (column_distance == row_distance) {
      return false;
    }
  }
  return true;
}

int main() {
  vector<int> columns(GRID_SIZE, 0);
  vector<vector<int>> results;
  PlaceQueens(0, columns, results);

  cout << "Number of solutions are " << results.size() << "\n";
  for (int i = 0; i < 4; i++) {
    cout << "Solution " << i << "\n";
    for (int j = 0; j < results[i].size(); ++j) {
      cout << "row - " << j << " col - " << results[i][j] << "\n";
    }
    cout << "------------------\n";
  }

  return 0;
}
