SOURCE = chap1.c
OUTPUT = chap1
WARNINGS = -Wall -Wextra
FLAGS += $(WARNINGS) 
FLAGS += $(LIBS) 

run: compile
	./$(OUTPUT)

compile:
	clang $(FLAGS) $(SOURCE) -o $(OUTPUT) 

test:
	pytest chap1_test.py
	# ./$(OUTPUT)

linux-install:
	pip install .

win-install:
	py setup.py install
	

clean:
	rm -rf build dist *.egg-info *.cpython-311-x86_64-linux-gnu.so __pycache__ $(OUTPUT)

check:
	cbmc $(SOURCE)
	esbmc $(SOURCE)
	cppcheck $(SOURCE)
	frama-c -eva $(SOURCE)

