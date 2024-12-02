#include "stdint.h"
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define EPSILON 1e-9

// testing
bool are_almost_equal(double a, double b, double epsilon) {
  return fabs(a - b) < epsilon;
}

double mean_double(const double array[], const size_t len) {
  assert(array != NULL && "check valid array");
  assert(len >= 1);

  double sum = 0;

  for (int i = 0; i < len; ++i) {
    assert(sum + array[i] > sum && "check overflow");

    sum += array[i];
  }

  return sum / len;
}

double mean_int(const int array[], const size_t len) {
  assert(array != NULL && "check valid array");
  assert(len >= 1);

  long sum = 0;

  for (int i = 0; i < len; ++i) {
    assert(sum + array[i] > sum && "check overflow");

    sum += array[i];
  }

  return (double)sum / len;
}

void test_mean_1() {

  int arr[] = {1, 2, 0x03};

  // printf("Mean: %lf\n", mean(arr, sizeof(arr) / sizeof(arr[0])));
  size_t len = sizeof(arr) / sizeof(arr[0]);
  assert(are_almost_equal(mean_int(arr, len), 2.0, EPSILON));
}

int main() { test_mean_1(); }
