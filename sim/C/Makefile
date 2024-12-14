SOURCE = chap1.c
TEST_SOURCE = chap1_test.c
OUTPUT = chap1

WARNINGS = -Wall -Wextra -pedantic
FLAGS += $(WARNINGS) 
FLAGS += $(LIBS) 

TEST_FUNCTION = mean_double

run: test

compile:
	clang $(FLAGS) $(SOURCE) -o $(OUTPUT) 

test:
	# pytest chap1_test.py
	clang $(FLAGS) $(TEST_SOURCE) && ./a.out

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
