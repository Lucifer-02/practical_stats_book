#include "chap1.c"

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

void test_trim_mean_1(void) {
  double const arr[] = {0, 1, 2, 0};
  size_t const len = sizeof(arr) / sizeof(arr[0]);
  size_t const trim = 1;
  // printf("\nMean: %lf\n", trim_mean(arr, len, trim));
  assert(trim_mean(arr, len, trim) == 0.5);
}

void test_trim_mean_2(void) {
  double const arr[] = {0, 0, 1, 2};
  size_t const len = sizeof(arr) / sizeof(arr[0]);
  size_t const trim = 1;
  // printf("\nMean: %lf\n", trim_mean(arr, len, trim));
  assert(trim_mean(arr, len, trim) == 0.5);
}

void test_trim_mean_3(void) {
  double const arr[] = {1, 2, 0, 0};
  size_t const len = sizeof(arr) / sizeof(arr[0]);
  size_t const trim = 1;
  // printf("\nMean: %lf\n", trim_mean(arr, len, trim));
  assert(trim_mean(arr, len, trim) == 0.5);
}

int main(void) {
  test_mean_double_1();
  test_median_double_1();
  test_trim_mean_1();
  test_trim_mean_2();
  test_trim_mean_3();
}
