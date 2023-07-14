CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11

SRC_FILES=smart_calc_v1/stack.c smart_calc_v1/smart_calc_v1.c
HEADER_FILES=smart_calc_v1/smart_calc_v1.h

CPP_FILES=$(wildcard smart_calc_v1/*.cpp)

TEST_SRC=tests/tests.c

ifeq ($(shell uname), Linux)
	LIB_CHECK=-lcheck -lm -lpthread -lrt -lsubunit
else
# LIB_CHECK=-lcheck -lm
	LIB_CHECK=-lm $(shell pkg-config --cflags --libs check)
endif

all: test

install:
	cd smart_calc_v1/ && mkdir build/
	cd smart_calc_v1/build/ && qmake ../smart_calc.pro && make
	open smart_calc_v1/build/smart_calc.app

uninstall:
	rm -rf smart_calc_v1/build

clean:
	rm -rf smart_calc_v1/*.o
	rm -rf smart_calc_v1/*.a
	rm -rf smart_calc_v1/test
	rm -rf *.gcno *.gcda
	rm -rf gcov_report
	rm -rf smart_calc_v1/*.info
	rm -rf report
	rm -rf smart_calc_v1/build
	rm -rf ../*.tar
	rm -rf smart_calc_v1/.clang-format

dist: clean
	cd ..
	tar -cf ../smart_calc_v1.tar smart_calc_v1 Makefile documentation.html

test:
	$(CC) --coverage smart_calc_v1/*.c $(TEST_SRC) -o test $(LIB_CHECK)
	./test
# leaks -atExit -- ./test
	rm -rf test *.gcda *.gcno

gcov_report:
	$(CC) $(CFLAGS) --coverage $(SRC_FILES) $(TEST_SRC) $(LIB_CHECK) -o gcov_report
	./gcov_report
	lcov -o gcov_report.info -c -d .
	genhtml -o report gcov_report.info
	open ./report/index.html
	rm -rf *.gcno *.gcda *.info gcov_report

style_test:
	clang-format -n -style=google $(SRC_FILES) $(HEADER_FILES) $(CPP_FILES) smart_calc_v1/*.h
	clang-format -i -style=google $(SRC_FILES) $(HEADER_FILES) $(CPP_FILES) smart_calc_v1/*.h