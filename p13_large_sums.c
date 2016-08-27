#include <stdio.h>
#include <stdlib.h>


int SumLast40Digits(char *line_ptr[]) {
  int col = 0;
  int line_num = 0;
  int num_lines = 100;

  int carry = 0;
  // col goes from the unit's place, ten's place, hundred's place and so on.
  for (col = 0; col < 50; ++col) {
    int column_sum = carry;
    for (line_num = 0; line_num < num_lines; ++line_num) {
      column_sum += (int)line_ptr[line_num][49 - col] - '0';
    }
    carry = column_sum/10;
  }
  return carry;
}

/* line_ptr  - is an array pointers to each line. Each line contains one 50 digits number.
 * carry     - is the carry from adding the last 40 digits
 * result_sum_first_10 - is an array of digits that are obtained from adding the numbers.
 *                       Pre-allocate it to a size of 10.
 *                       zeroth index of the array is actually the units place in the 
 *                       final sum.
 */
void SumFirst10Digits(char *line_ptr[], int carry, int *result_sum_first_10) {
  int col = 0;
  int line_num = 0;
  int column_sum = 0;
  int num_lines = 100;

  // col goes from the unit's place, ten's place, hundred's place and so on.
  for (col = 40; col < 49; ++col) {
    column_sum = carry;
    for (line_num = 0; line_num < num_lines; ++line_num) {
      column_sum += (int)line_ptr[line_num][49 - col] - '0';
    }
    carry = column_sum/10;
    result_sum_first_10[col - 40] = column_sum%10;
    // printf("carry from this column is %d\n", carry);
  }

  column_sum = carry;
  printf("column_sum before last column is %d\n", column_sum);
  printf("Value of col is %d\n", col);
  // for the last column, no need of generating a carry
  for (line_num = 0; line_num < num_lines; ++line_num) {
    column_sum += ((int)line_ptr[line_num][49 - col] - '0');
    /* printf("line in the loop is %d\n", (int)line_ptr[line_num][49 - col] - '0'); */
  }
  result_sum_first_10[col - 40] = column_sum;
}

int main(int argc, char *argv[]) {
  FILE *fp;
  int i = 0;
  int j = 0;
  char *line;
  int num_digits = 50;
  int num_lines = 100;
  char *line_ptr[num_lines];

  /* adding 1 for the \0 */
  if (argc == 1) { /* no args */
    fprintf(stderr, "Please provide a data file as argument\n");
    return 1;
  } else if (argc == 2) {
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
      fprintf(stderr, "Unable to open %s\n", argv[1]);
      return 2;
    }
    printf("Reading in lines\n");
    /* the problem statement says the number of lines is 100. */
    for (i = 0; i < num_lines; ++i) {
      line = (char*)malloc(num_digits+2);
      // num_digits + 1 characters are read. +1 for \n character.
      fgets(line, num_digits+2, fp);

      for (j = 0; j < 50; ++j) {
        printf("%c ", line[j]);
      }
      printf("\n");
      line_ptr[i] = line;
    }


    int carry = SumLast40Digits(line_ptr);
    fprintf(stdout, "Carry from the Last 40 Digits is %d\n", carry);
    // zeroth index is unit's place, index 1 is the ten's place and so on.
    int result_sum_first_10[10];
    SumFirst10Digits(line_ptr, carry, result_sum_first_10);
    // Printing the sum
    printf("First few digits of the sum are here:\n");
    for (i = 9; i >= 0; --i) {
      fprintf(stdout, "%d", result_sum_first_10[i]);
    }
    fprintf(stdout, "\n");
  }
  return 0;
}
