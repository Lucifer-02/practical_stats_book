#include "stdint.h"
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EPSILON 1e-6

// testing
bool are_almost_equal(double a, double b, double epsilon) {
  return fabs(a - b) < epsilon;
}

double mean_double(const double array[], const size_t len) {
  assert(array != NULL && "check valid array");
  assert(len >= 1);

  double sum = 0;

  for (size_t i = 0; i < len; ++i) {
    assert(!isinf(sum) && "check overflow");

    sum += array[i];
  }

  return sum / len;
}

double mean_int(const int array[], const size_t len) {
  assert(array != NULL && "check valid array");
  assert(len >= 1);

  long sum = 0;

  for (size_t i = 0; i < len; ++i) {
    assert((sum + array[i]) > sum && "check overflow");

    sum += array[i];
  }

  return (double)sum / len;
}

// compare function, compares two elements
int double_compare(const void *num1, const void *num2) {
  if (*(double *)num1 > *(double *)num2)
    return 1;
  else
    return -1;
}

double median_double(const double array[], const size_t len) {
  assert(len >= 1);

  double *const copy = (double *)malloc(len * sizeof(double));
  if (copy == NULL) {
    abort();
  }
  memcpy(copy, array, len * sizeof(double));

  qsort(copy, len, sizeof(typeof(copy[0])), double_compare);

  double median;
  if (len % 2 == 1) {
    median = copy[len / 2];
  } else {
    median = (copy[len / 2] + copy[len / 2 - 1]) / 2;
    assert(!isinf(median) && "check overflow");
  }

  free(copy);
  return median;
}

void test_mean_double_1() {

  const double arr[] = {1, 2, 0x03};

  const size_t len = sizeof(arr) / sizeof(arr[0]);
  assert(are_almost_equal(mean_double(arr, len), 2.0, EPSILON));
}

void test_median_double_1() {

  const double arr[] = {2, 1, 3, 4};
  const size_t len = sizeof(arr) / sizeof(arr[0]);

  // printf("Median: %lf\n", median_double(arr, len));
  assert(are_almost_equal(median_double(arr, len), 2.5, EPSILON));
}

int main() {
  // test_mean_double_1();
  test_median_double_1();
}
