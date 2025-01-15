#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mylib/slice.c"

typedef Slice Data;

double const *get_ele(Data const data, size_t const index) {
  return (double *)get_item(data, index);
}
Data copy_data(Data const data) { return copy_slice(data); }
void qsort_data(Data const data) { qsort_slice(data); }
Data make_data(Data const data, size_t low, size_t high) {
  return make_slice(data, low, high);
}
Data sorted_data(Data const data) { return sorted_slice(data); }

void free_data(Data const data) { free_slice(data); }

double mean_double(Data const data) {
  assert(data.len >= 1);

  double sum = 0;

  for (size_t i = 0; i < data.len; ++i) {
    sum += *get_ele(data, i);
    assert(!isinf(sum) && "check overflow");
  }

  return sum / data.len;
}

double median_double(Data const data) {
  assert(data.len >= 1);

  Data const sorted_copy = sorted_slice(data);

  double median;
  if (data.len % 2 == 1) {
    median = *get_ele(sorted_copy, sorted_copy.len / 2);
  } else {
    median = (*get_ele(sorted_copy, sorted_copy.len / 2) +
              *get_ele(sorted_copy, sorted_copy.len / 2 - 1)) /
             2;
  }

  free_data(sorted_copy);

  assert(!isinf(median) && "check overflow");
  return median;
}

double trim_mean(Data const data, size_t const trim) {
  assert(data.len > trim * 2 && "the trimming not over data length");

  Data const sorted_copy = sorted_slice(data);

  // Data const trimmed_data = {.pointer = sorted_copy + trim,
  //                             .len = len - 2 * trim,
  //                             .item_size = sizeof(double)};
  //
  Data const trimmed_data =
      make_slice(sorted_copy, trim, sorted_copy.len - trim);

  assert(trimmed_data.len == sorted_copy.len - 2 * trim &&
         "check valid trimmed");

  double const mean = mean_double(trimmed_data);

  free_data(sorted_copy);

  return mean;
}

double weighted_mean(Data const data, Slice const weights) {

  assert(data.len == weights.len && "each weight must belong to an entry");

  double weighted = 0.0;
  double sum_weights = 0.0;

  for (size_t i = 0; i < data.len; ++i) {
    weighted += (*get_ele(data, i)) * (*get_ele(weights, i));
    assert(!isinf(weighted) && "overflow check");
    sum_weights += *get_ele(weights, i);
    assert(!isinf(sum_weights) && "overflow check");
  }

  assert(sum_weights != 0 && "total weight can not be zero");
  return weighted / sum_weights;
}

double var(Data const data, size_t ddof) {
  assert(data.len > 0);
  assert(ddof < data.len &&
         "degree of freedom delta is always < length of data");

  double sum_squares = 0;
  double const mean = mean_double(data);

  for (size_t i = 0; i < data.len; ++i) {
    sum_squares += pow(*get_ele(data, i) - mean, 2);
    assert(!isinf(sum_squares) && "overflow check");
  }

  return sum_squares / (data.len - ddof);
}

double std(Data const data, size_t ddof) {
  assert(data.len > 0);
  assert(ddof < data.len &&
         "degree of freedom delta is always < length of data");

  return sqrt(var(data, ddof));
}

bool is_percent(double const percent) {
  if (percent > 0.0 && percent < 1.0) {
    return true;
  }
  return false;
}

// ref: https://numpy.org/doc/2.1/reference/generated/numpy.quantile.html
double quantile(Data const data, double const q) {
  assert(data.len > 0);
  assert(is_percent(q));

  Data sorted = sorted_data(data);

  double j = -1; // -1 is dummy number to check
  double const g = modf(q * (data.len - 1), &j);
  assert(j >= 0);

  double const result =
      (1 - g) * (*get_ele(sorted, j)) + g * (*get_ele(sorted, j + 1));

  free_data(sorted);
  return result;
}

// this main function for static analysis and quick test

// int main(void) {
//
//   double const arr[] = {1, 2, 3, 4};
//
//   Data const data = {
//       .pointer = (char *)arr, .len = 4, .item_size = sizeof(double)};
//
//   printf("%lf\n", quantile(data, 0.25));
//   return EXIT_SUCCESS;
// }
