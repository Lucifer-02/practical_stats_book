#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mylib/common.c"
#include "mylib/slice.c"

double mean_double(Slice const data) {
  assert(data.len >= 1);

  double sum = 0;

  for (size_t i = 0; i < data.len; ++i) {
    sum += *(double *)get_item(data, i);
    assert(!isinf(sum) && "check overflow");
  }

  return sum / data.len;
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

double trim_mean(double const array[], size_t const len, size_t const trim) {
  assert(len > trim * 2 && "the trimming not over data length");

  double *const copy = (double *)malloc(len * sizeof(double));
  if (copy == NULL) {
    abort(); // Allocation failed!
  }
  memcpy(copy, array, len * sizeof(double));

  qsort(copy, len, sizeof(double), double_compare);

  Slice const trimmed_data = {.pointer = copy + trim,
                              .len = len - 2 * trim,
                              .item_size = sizeof(double)};

  double const mean = mean_double(trimmed_data);

  free(copy);

  return mean;
}

double weighted_mean(Slice const data, Slice const weights) {

  assert(data.len == weights.len && "each weight must belong to an entry");

  double weighted = 0.0;
  double sum_weights = 0.0;

  for (size_t i = 0; i < data.len; ++i) {
    weighted += *(double *)get_item(data, i) * *(double *)get_item(weights, i);
    assert(!isinf(weighted) && "overflow check");
    sum_weights += *(double *)get_item(weights, i);
    assert(!isinf(sum_weights) && "overflow check");
  }

  assert(sum_weights != 0 && "total weight can not be zero");
  return weighted / sum_weights;
}

// this main function for static analysis and quick test

// int main(void) {
//
//   double const arr[] = {0, 1, 2, 0};
//   double const weights[] = {1, 1, 1, 1};
//
//   Slice const data = {.pointer = arr, .len = 4, .item_size = sizeof(double)};
//   Slice const w = {.pointer = weights, .len = 4, .item_size =
//   sizeof(double)};
//
//   printf("%lf\n", weighted_mean(data, w));
//   return EXIT_SUCCESS;
// }
