#include <stdio.h>

void print_arr(double *arr, size_t len) {
  for (size_t i = 0; i < len; ++i) {
    printf("%lf ", arr[i]);
  }
  printf("\n");
}

// compare function, compares two elements
int double_compare(const void *num1, const void *num2) {
  if (*(double *)num1 > *(double *)num2)
    return 1;
  else
    return -1;
}
