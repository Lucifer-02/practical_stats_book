import numpy as np
from scipy import stats
from time import time

import mymodule


trim = 10
arr = np.random.rand(1000000)


start = time()
result = stats.trim_mean(arr, proportiontocut=trim / len(arr))
end = time()
print(f"result: {result}, in {end - start}")

start = time()
result = mymodule.trim_mean(array=arr, trim=trim)
end = time()
print(f"result: {result}, in {end - start}")

print(arr)
