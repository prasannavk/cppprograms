/* NOT COMPLETE */
#include <stdio.h>
#include <stdlib.h>


int SumFirst40Digits(char *line_ptr[]) {
  int i = 0;
  int line_num = 0;

  for (i = 0; i < 40; ++i) {
    int column_sum = 0;
    for (line_num = 0; line_num < 100; ++line_num) {
      column_sum += (int)line_ptr[line_num][49 - i];
    }
  }
}

int main(int argc, char *argv[]) {
  FILE *fp;
  int i = 0;
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
    /* the problem statement says the number of lines is 100. */
    for (i = 0; i < num_lines; ++i) {
      line = (char*)malloc(num_digits+1);
      fgets(line, num_digits, fp);
      line_ptr[i] = line;
    }

    int carry = SumFirst40Digits(line_ptr);
  }
  return 0;
}
