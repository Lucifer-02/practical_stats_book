SOURCE = chap1.c
C_TEST_SOURCE = chap1_test.c
C_SOURCE_DIR= src
PY_TEST_SOURCE = chap1_test.py
PY_TEST_DIR = py_tests
OUTPUT = chap1
LIBS = -lm

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
	clang $(FLAGS) $(C_SOURCE_DIR)/$(C_TEST_SOURCE) && ./a.out
	uv run pytest $(PY_TEST_DIR)/$(PY_TEST_SOURCE)

linux-install: uninstall wheel
	uv pip install ./dist/c-0.1.0-cp311-cp311-linux_x86_64.whl

win-install:
	py setup.py install

uninstall:
	rm -f ./.venv/lib64/python3.11/site-packages/mymodule.cpython-311-x86_64-linux-gnu.so
	
wheel:
	uv run setup.py bdist_wheel

clean:
	rm -rf build dist *.egg-info *.cpython-311-x86_64-linux-gnu.so __pycache__ $(OUTPUT) a.out infer-out/ chap1.o

check:
	# cbmc $(SOURCE) --function $(TEST_FUNCTION)
	# esbmc $(SOURCE) --function $(TEST_FUNCTION)
	# cppcheck $(SOURCE)
	# frama-c -eva $(SOURCE) -main $(TEST_FUNCTION)
	infer run -- clang -c $(SOURCE)
