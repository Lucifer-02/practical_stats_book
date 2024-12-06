#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double mean_double(const double array[], const size_t len) {
  assert(array != NULL && "check valid array");
  assert(len >= 1);

  double sum = 0;

  for (size_t i = 0; i < len; ++i) {
    sum += array[i];
    assert(!isinf(sum) && "check overflow");
  }

  return sum / len;
}

double mean_int(const int array[], const size_t len) {
  assert(array != NULL && "check valid array");
  assert(len >= 1);

  long sum = 0;

  for (size_t i = 0; i < len; ++i) {
    sum += array[i];
    assert((sum + array[i]) > sum && "check overflow");
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
    abort(); // Allocation failed!
  }
  memcpy(copy, array, len * sizeof(double));

  qsort(copy, len, sizeof(double), double_compare);

  double median;
  if (len % 2 == 1) {
    median = copy[len / 2];
  } else {
    median = (copy[len / 2] + copy[len / 2 - 1]) / 2;
  }

  free(copy);

  assert(!isinf(median) && "check overflow");
  return median;
}

typedef struct {
  const void *pointer;
  const size_t len;
} Slice;

void print_arr(double *arr, size_t len) {
  for (size_t i = 0; i < len; ++i) {
    printf("%lf ", arr[i]);
  }
  printf("\n");
}

double trimmed_mean(double const array[], size_t const len, size_t const trim) {
  assert(len > trim * 2 && "the trimming not over data length");

  // print_arr(array, len);

  double *const copy = (double *)malloc(len * sizeof(double));
  if (copy == NULL) {
    abort(); // Allocation failed!
  }
  memcpy(copy, array, len * sizeof(double));

  qsort(copy, len, sizeof(double), double_compare);

  // print_arr(copy, len);

  Slice const trimmed_data = {.pointer = copy + trim, .len = len - 2 * trim};

  // print_arr((double *)trimmed_data.pointer, trimmed_data.len);

  double const mean = mean_double(trimmed_data.pointer, trimmed_data.len);

  free(copy);

  return mean;
}

//================ TESTS ========================

#define EPSILON 1e-8

// testing
bool are_almost_equal(double a, double b, double epsilon) {
  return fabs(a - b) < epsilon;
}
void test_mean_double_1(void) {

  const double arr[] = {1, 2, 3};

  const size_t len = sizeof(arr) / sizeof(arr[0]);
  assert(are_almost_equal(mean_double(arr, len), 2.0, EPSILON));
}

void test_median_double_1(void) {

  const double arr[] = {2, 1, 3, 4};
  const size_t len = sizeof(arr) / sizeof(arr[0]);

  // printf("Median: %lf\n", median_double(arr, len));
  assert(are_almost_equal(median_double(arr, len), 2.5, EPSILON));
}

void test_trimmed_mean_1(void) {
  double const arr[] = {0, 1, 2, 0};
  size_t const len = sizeof(arr) / sizeof(arr[0]);
  size_t const trim = 1;
  // printf("\nMean: %lf\n", trimmed_mean(arr, len, trim));
  assert(trimmed_mean(arr, len, trim) == 0.5);
}

void test_trimmed_mean_2(void) {
  double const arr[] = {0, 0, 1, 2};
  size_t const len = sizeof(arr) / sizeof(arr[0]);
  size_t const trim = 1;
  // printf("\nMean: %lf\n", trimmed_mean(arr, len, trim));
  assert(trimmed_mean(arr, len, trim) == 0.5);
}

void test_trimmed_mean_3(void) {
  double const arr[] = {1, 2, 0, 0};
  size_t const len = sizeof(arr) / sizeof(arr[0]);
  size_t const trim = 1;
  // printf("\nMean: %lf\n", trimmed_mean(arr, len, trim));
  assert(trimmed_mean(arr, len, trim) == 0.5);
}

int main(void) {
  test_mean_double_1();
  test_median_double_1();
  test_trimmed_mean_1();
  test_trimmed_mean_2();
  test_trimmed_mean_3();
}
