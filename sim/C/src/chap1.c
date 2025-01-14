#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include "mylib/common.c"
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

double mean_int(Slice const data) {
  assert(data.len >= 1);

  long sum = 0;

  for (size_t i = 0; i < data.len; ++i) {
    long e = *(long *)get_item(data, i);
    sum += e;
    assert((sum + e) > sum && "check overflow");
  }

  return (double)sum / data.len;
}

double median_double(Slice const data) {
  assert(data.len >= 1);

  Slice const sorted_copy = sorted_slice(data);

  double median;
  if (data.len % 2 == 1) {
    median = *(double *)get_item(sorted_copy, sorted_copy.len / 2);
  } else {
    median = (*(double *)get_item(sorted_copy, sorted_copy.len / 2) +
              *(double *)get_item(sorted_copy, sorted_copy.len / 2 - 1)) /
             2;
  }

  free_slice(sorted_copy);

  assert(!isinf(median) && "check overflow");
  return median;
}

double trim_mean(Slice const data, size_t const trim) {
  assert(data.len > trim * 2 && "the trimming not over data length");

  Slice const sorted_copy = sorted_slice(data);

  // Slice const trimmed_data = {.pointer = sorted_copy + trim,
  //                             .len = len - 2 * trim,
  //                             .item_size = sizeof(double)};
  //
  Slice const trimmed_data =
      make_slice(sorted_copy, trim, sorted_copy.len - trim);

  assert(trimmed_data.len == sorted_copy.len - 2 * trim &&
         "check valid trimmed");

  double const mean = mean_double(trimmed_data);

  free_slice(sorted_copy);

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

double var(Slice const data, size_t ddof) {
  assert(data.len > 0);
  assert(ddof < data.len &&
         "degree of freedom delta is always < length of data");

  double sum_squares = 0;
  double const mean = mean_double(data);

  for (size_t i = 0; i < data.len; ++i) {
    sum_squares += pow(*(double *)get_item(data, i) - mean, 2);
    assert(!isinf(sum_squares) && "overflow check");
  }

  return sum_squares / (data.len - ddof);
}

double std(Slice const data, size_t ddof) {
  assert(data.len > 0);
  assert(ddof < data.len &&
         "degree of freedom delta is always < length of data");

  return pow(var(data, ddof), 0.5);
}

// this main function for static analysis and quick test
//
// int main(void) {
//
//   double const arr[] = {0, 1, 2, 0};
//
//   Slice const data = {
//       .pointer = (char *)arr, .len = 4, .item_size = sizeof(double)};
//
//   printf("%lf\n", var(data, 1));
//   return EXIT_SUCCESS;
// }
