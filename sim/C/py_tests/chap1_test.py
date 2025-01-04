import unittest

import numpy as np
from scipy import stats

import mymodule


class TestChap1(unittest.TestCase):
    def setUp(self) -> None:
        self.delta = 1e-6

    def tearDown(self):
        # This method is run after every test
        print("Teardown completed")

    def test_mean_1(self):
        arr = np.array([1, 2, 3])

        self.assertEqual(np.mean(arr), mymodule.mean_list(arr))

    def test_mean_2(self):
        arr = np.linspace(start=-10, stop=123, num=100_000_000)

        self.assertAlmostEqual(np.mean(arr), mymodule.mean_list(arr), delta=self.delta)

    def test_mean_3(self):
        arr = np.array([0])

        self.assertEqual(np.mean(arr), mymodule.mean_list(arr))

    def test_trim_mean_1(self):
        trim = 1
        arr = np.array([0, 1, 2, 0])

        self.assertEqual(
            stats.trim_mean(arr, proportiontocut=trim / len(arr)),
            mymodule.trim_mean(array=arr, trim=1),
        )

    def test_trim_mean_2(self):
        trim = 20
        arr = np.random.rand(1_000_000)

        self.assertAlmostEqual(
            stats.trim_mean(arr, proportiontocut=trim / len(arr)),
            mymodule.trim_mean(array=arr, trim=trim),
            delta=self.delta,
        )

    def test_weighted_mean_1(self):
        SIZE = 1_0_000

        data = np.random.rand(SIZE)
        weights = np.random.rand(SIZE)

        self.assertAlmostEqual(
            np.average(data, weights=weights),
            mymodule.weighted_mean_list(data_list=data, weights=weights),
            delta=self.delta,
        )

    def test_weighted_mean_2(self):
        SIZE = 1_000_000

        data = np.random.rand(SIZE)
        weights = np.random.rand(SIZE)

        self.assertAlmostEqual(
            np.average(data, weights=weights),
            mymodule.weighted_mean_list(data_list=data, weights=weights),
            delta=self.delta,
        )
