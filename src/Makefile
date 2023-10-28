CXX = g++
CXXFLAGS = -O2 -Wall -Werror -Wextra -std=c++17

LGFLAGS = -lgtest

SCR_TEST = tests/*.cpp
SCR_MODEL = Model/model.cpp

all: install tests

install:
	@mkdir build/
	@cd build/ && qmake ../smartcalc.pro && make
	@open build/smartcalc.app
#@./build/smartcalc.app/Contents/MacOS/smartcalc

open:
	@open build/smartcalc.app

uninstall:
	rm -rf build/

clean:
	rm -rf build/
	rm -rf test
	rm -rf *.gcno *.gcda

dist: clean
	@cd ..
	tar -cf ../smartcalc_v2.tar Controller/ Model/ QCustomPlot/ View/ Makefile main.cpp smartcalc.pro

tests:
	@$(CXX) $(CXXFLAGS) --coverage $(SCR_TEST) $(SCR_MODEL) $(LGFLAGS) -o test
	@./test
	@rm -rf test *.gcda *.gcno

.PHONY: all install uninstall clean dist tests open