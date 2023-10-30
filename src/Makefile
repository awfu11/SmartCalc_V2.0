CXX = g++
CXXFLAGS = -O2 -Wall -Werror -Wextra -std=c++17

LDFLAGS = $(shell pkg-config --cflags --libs gtest)

SCR_TEST = tests/*.cpp
SCR_MODEL = Model/model.cpp

OS := $(shell uname -s)
ifeq ($(OS), Linux)
  OPEN = ./build/smartcalc
endif
ifeq ($(OS), Darwin)
	OPEN = open build/smartcalc.app
endif

all: install

install:
	@mkdir build/ && cd build/ && qmake ../smartcalc.pro && make
	$(OPEN)

open:
	$(OPEN)

uninstall:
	rm -rf build/

clean:
	rm -rf build/ test *.gcno *.gcda

dist: clean
	cd ..
	tar -cf ../smartcalc_v2.tar Controller/ Model/ QCustomPlot/ View/ Makefile main.cpp smartcalc.pro

tests:
	@$(CXX) $(CXXFLAGS) --coverage $(SCR_TEST) $(SCR_MODEL) $(LDFLAGS) -o test && ./test
	@rm -rf *.gcda *.gcno

.PHONY: all install uninstall clean dist tests open
