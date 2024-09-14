FLAG = -Wall -Werror -Wextra -std=c11 -g
FILES=$(wildcard Model/*.c)
OBJ=$(patsubst %.c,%.o, ${FILES})
GCO=--coverage
UNAME := $(shell uname)
TEST= Tests/test_main_calc.c Tests/test_credit_calc.c Tests/main.c Tests/test_deposit_calc.c
QMAKE_PRESENT=$(shell which qmake)

ifeq ($(UNAME), Linux)
	GFLAGS = -lcheck -lpthread -lrt -lm -lsubunit
	QTFLAGS = CONFIG+=qtquickcompiler
	RUNINSTR = ./build/SmartCalc
endif

ifeq ($(UNAME), Darwin)
	GFLAGS = -lcheck
	QTFLAGS = -spec macx-clang CONFIG+=qtquickcompiler
	RUNINSTR = open build/SmartCalc.app
endif

ifndef QMAKE_PRESENT
    $(error "No qmake in found in $(PATH), consider installing qmake and Qt on your system")
endif

all: install run

install: uninstall
	mkdir build
	cd build && qmake ../SmartCalc/SmartCalc.pro $(QTFLAGS) && /usr/bin/make -j8

uninstall:
	rm -rf build

run:
	$(RUNINSTR)

dvi:
	open ./Use_SmartCalc_V01.md
	
dist: clean
	@mkdir SmartCalc_v1.0/
	@mkdir SmartCalc_v1.0/src
	@cp -R Makefile Model SmartCalc Use_SmartCalc_V01.md Tests SmartCalc_v1.0/src
	@tar cvzf SmartCalc_v1.0.tgz SmartCalc_v1.0/
	@rm -rf build SmartCalc_v1.0

dist_delete:
	rm -rf SmartCalc_v1.0 SmartCalc_v1.0.tgz 

test: clean 
	@gcc -g $(FLAG) -o test $(TEST) $(FILES) $(GFLAGS)
	./test

main: clean
	gcc $(FLAG) -g -o main $(FILES)
	./main

gcov_report: clean
	@gcc $(FLAG) $(GCO) $(TEST) $(FILES) -o test $(GFLAGS)
	./test
	lcov --capture --directory . --output-file=coverage.info
	genhtml coverage.info --output-directory=res
	open ./res/index.html
	-rm -rf *.dSYM test *.gcda *.gcno *.info

clean:
	rm -rf build
	-rm -rf main *.dSYM test *.gcda *.gcno *.info ./res
	rm -rf *.tgz
	clear

leaks: clean test
	@leaks -atExit -- ./test | grep LEAK:

valgrind: clean test
	@valgrind --tool=memcheck --leak-check=yes ./test

style: clean
	clang-format -style=Google -i Tests/*.c Tests/*.h
	clang-format -style=Google -i Model/*.c Tests/*.h
	clang-format -style=Google -i SmartCalc/*.cpp Tests/*.h

style_check: clean
	clang-format -style=Google -n Tests/*.c Tests/*.h
	clang-format -style=Google -n Model/*.c Tests/*.h
	clang-format -style=Google -n SmartCalc/*.cpp Tests/*.h