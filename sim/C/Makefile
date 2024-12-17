SOURCE = chap1.c
C_TEST_SOURCE = chap1_test.c
C_SOURCE_DIR= src
PY_TEST_SOURCE = chap1_test.py
PY_TEST_DIR = py_tests
OUTPUT = chap1

WARNINGS = -Wall -Wextra -pedantic
FLAGS += $(WARNINGS) 
FLAGS += $(LIBS) 

TEST_FUNCTION = mean_double

# this will not work with make, I put it here to save activate venv command
env:
	source .mystats/bin/activate


run: test

compile:
	clang $(FLAGS) $(C_SOURCE_DIR)/$(SOURCE) -o $(OUTPUT) 

test:
	# pytest $(PY_TEST_DIR)/$(PY_TEST_SOURCE)
	clang $(FLAGS) $(C_SOURCE_DIR)/$(C_TEST_SOURCE) && ./a.out

linux-install:
	pip install .

win-install:
	py setup.py install
	
wheel:
	python3 setup.py bdist_wheel

clean:
	rm -rf build dist *.egg-info *.cpython-311-x86_64-linux-gnu.so __pycache__ $(OUTPUT) a.out infer-out/ chap1.o

check:
	# cbmc $(SOURCE) --function $(TEST_FUNCTION)
	# esbmc $(SOURCE) --function $(TEST_FUNCTION)
	# cppcheck $(SOURCE)
	# frama-c -eva $(SOURCE) -main $(TEST_FUNCTION)
	infer run -- clang -c $(SOURCE)
