SOURCE = chap1.c
OUTPUT = chap1
FLAGS = -Wall -Wextra

run: py

compile:
	clear
	clang $(FLAGS) $(SOURCE) -o $(OUTPUT) && ./$(OUTPUT)

py:
	pip install .

clean:
	rm -rf build dist *.egg-info *.cpython-311-x86_64-linux-gnu.so __pycache__ $(OUTPUT)

check:
	cbmc $(SOURCE)
	esbmc $(SOURCE)
	cppcheck $(SOURCE)
	frama-c -eva $(SOURCE)

