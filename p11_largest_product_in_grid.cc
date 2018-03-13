#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using std::cout;
using std::vector;

int main() {
  std::ifstream fin("data_p11_product_grid.txt");
  int num_columns = 20;
  int num_rows = 20;
  vector<vector<int> > sequence(num_rows, vector<int>(0));
  
  for (int i = 0; i < num_rows; ++i) {
    sequence[i].reserve(num_columns);
    copy_n(std::istream_iterator<int>(fin), num_columns,
           back_inserter(sequence[i]));

    for (auto num : sequence[i]) {
      cout << num << " ";
    }
    cout << "\n";
  }
  vector<vector<long int> > row_product_mat(num_rows, vector<long int>(num_columns, 1));
  cout << "Row Product is :\n";

  long int max = 0;
  // Find the row product(multiplying 4 numbers in a row) matrix
  for (int i = 0; i < num_rows; ++i) {
    for (int j = 0; j < num_columns - 3; ++j) {
      for (int q = j; q < j + 4; ++q) {
        row_product_mat[i][j] *= sequence[i][q];
      }
      if (row_product_mat[i][j] > max) {
        max = row_product_mat[i][j];
      }
    }
  }

  for (auto row_vec : row_product_mat) {
    for (auto product : row_vec) {
      cout << product << " ";
    }
    cout << "\n";
  }

  vector<vector<long int> > col_product_mat(num_rows, vector<long int>(num_columns, 1));
  // Find the column product(multiplying 4 numbers in a row) matrix
  for (int i = 0; i < num_rows - 3; ++i) {
    for (int j = 0; j < num_columns; ++j) {
      for (int p = i; p < i + 4; ++p) {
        col_product_mat[i][j] *= sequence[p][j];
      }
      if (col_product_mat[i][j] > max) {
        max = col_product_mat[i][j];
      }
    }
  }

  cout << "Column Product is :\n";
  for (auto col_vec : col_product_mat) {
    for (auto product : col_vec) {
      cout << product << " ";
    }
    cout << "\n";
  }

  vector<vector<long int> > diag_product_mat(num_rows, vector<long int>(num_columns, 1));
  for (int i = 0; i < num_rows - 3; ++i) {
    for (int j = 0; j < num_columns - 3; ++j) {
      for (int p = i, q = j; p < i + 4 && q < j + 4; ++p, ++q) {
        diag_product_mat[i][j] *= sequence[p][q];
      }
      if (diag_product_mat[i][j] > max) {
        max = diag_product_mat[i][j];
      }
    }
  }
  cout << "Diagonal Product is :\n";
  for (auto diag_vec : diag_product_mat) {
    for (auto product : diag_vec) {
      cout << product << " ";
    }
    cout << "\n";
  }
#if 1
  vector<vector<long int> > left_diag_product_mat(num_rows, vector<long int>(num_columns, 1));
  for (int i = 0; i < num_rows - 3; ++i) {
    for (int j = 3; j < num_columns; ++j) {
      for (int p = i, q = j; p < i + 4 && q > j - 4; p++, --q) {
        left_diag_product_mat[i][j] *= sequence[p][q];
      }
      if (left_diag_product_mat[i][j] > max) {
        max = left_diag_product_mat[i][j];
      }
    }
  }
  cout << "Diagonal Product is :\n";
  for (auto diag_vec : left_diag_product_mat) {
    for (auto product : diag_vec) {
      cout << product << " ";
    }
    cout << "\n";
  }
#endif

  cout << "The maximum product is " << max << "\n";
  return 0;
}
