SOURCE = chap1.c
OUTPUT = chap1
WARNINGS = -Wall -Wextra
FLAGS += $(WARNINGS) 
FLAGS += $(LIBS) 

run: py 
	python3 test.py

compile:
	clang $(FLAGS) $(SOURCE) -o $(OUTPUT) 

test:
	# ./$(OUTPUT)
	pytest *_test.py

py:
	pip install .

clean:
	rm -rf build dist *.egg-info *.cpython-311-x86_64-linux-gnu.so __pycache__ $(OUTPUT)

check:
	cbmc $(SOURCE)
	esbmc $(SOURCE)
	cppcheck $(SOURCE)
	frama-c -eva $(SOURCE)

