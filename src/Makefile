CC=g++ 
CFLAGS=-std=c++17 -Wall -Werror -Wextra -lstdc++
GCOV_FLAGS=-fprofile-arcs -ftest-coverage
CFILES= ./model/*.cc 
TEST_PATH=./Google_tests/*

OS = $(shell uname)

ifeq ($(OS), Darwin)
	LIBFLAGS = -lm -lgtest -lgtest_main -lstdc++
else
	LIBFLAGS=`pkg-config --cflags --libs gtest` -lpthread -lgtest -pthread -lrt -lm -lgmock
endif

all: clean tests

tests:
	$(CC) $(CFLAGS) $(LIBFLAGS) $(CFILES) $(TEST_PATH) -o test
	./test

clean:
	@rm -rf *.a \
	*.o \
	*.info \
	*.gcda \
	*.gcno \
	*.gcov \
	*.gch  \
	report \
	test \
	Archive_SmartCalc_v2.0.tgz

install:
	mkdir build
	cd calc2 && qmake && make && make clean && rm Makefile  && mv calc2.app ../build/


uninstall:
	@rm -rf ./build*

dvi:
	open readme.md

dist:
	tar cvzf Archive_SmartCalc_v2.0.tgz .

gcov_report:
	$(CC) $(CFILES) $(TEST_PATH) $(LIBFLAGS) $(GCOV_FLAGS) -lcheck -o test
	./test
	gcov test
	lcov --ignore-errors mismatch -t  "test" -c -d  ./  --no-external --output-file ./coverage.info
	genhtml coverage.info --output-directory ./report/
	open ./report/index.html

leaks: test
	CK_FORK=no leaks --atExit -- ./test

clang: 
	cp ../materials/linters/.clang-format ./
	clang-format -style=Google  -i -n  $(TEST_PATH) ./model/* ./controller/* ./view/* ./calc2/*.cpp
	rm .clang-format


