CC = gcc -g
FLAGS = -Wall -Werror -Wextra
PLATFORM = $(shell uname)
GTKFLAGS = `pkg-config --cflags --libs gtk+-3.0`
SRC = ./frontend/calc_mode.c ./frontend/menu.c ./frontend/graphic_mode.c ./frontend/help_graph.c ./frontend/credit_mode.c ./frontend/deposit_mode.c
BACK = ./backend/parsing_and_calc.c ./backend/stack/stack_num.c ./backend/stack/stack_sym.c ./backend/credit.c ./backend/deposit.c
OBJ = *.o
TESTS_SRC = tests.c
INC_CHECK = $(shell pkg-config --cflags --libs check)
LFLAGS = -fprofile-arcs -ftest-coverage
GCOV_FLAGS  = -fprofile-arcs -ftest-coverage -lgcov --coverage -lcheck -lm -lpthread
ifeq ($(PLATFORM), Linux)
OPEN = xdg-open 
else
OPEN = open
endif

PROJECT_NAME ?= SmartCalc_v1

PATH_BACKEND ?= ./backend/
PATH_FRONTEND ?= ./frontend/
PATH_BUILD ?= ./build/
PATH_DOCS ?= ./docs/

CUR_DATE ?= `date +"%Y.%m.%d"`
PATH_ARCHIVE ?= $(PROJECT_NAME)_$(CUR_DATE)

RM = rm -rf

MK := mkdir -p

all: clean install tests

install: uninstall
	mkdir ./bin
	$(CC) ./frontend/calc.c $(SRC) $(GTKFLAGS) $(BACK) -o ./bin/calc -lm

uninstall:
	rm -rf ./bin

dvi:
	mkdir -p docs
	doxygen Doxyfile
	mv html docs
	google-chrome docs/html/index.html


dist: clean
	@$(MK) $(PATH_ARCHIVE)
	@cp -r $(PATH_BACKEND) $(PATH_ARCHIVE)
	@cp -r $(PATH_FRONTEND) $(PATH_ARCHIVE)
	@cp Makefile $(PATH_ARCHIVE)
	@tar -czvf $(PATH_ARCHIVE).tar.gz $(PATH_ARCHIVE)
	@$(RM) $(PATH_ARCHIVE)


tests.a: ./backend/parsing_and_calc.c ./backend/stack/stack_num.c ./backend/stack/stack_sym.c ./backend/credit.c ./backend/deposit.c
	$(CC) -c --coverage $?
	ar -rcs $@ *.o
	ranlib $@
	rm -f *.o

tests: tests.a tests_/tests.c
	$(CC) tests_/tests.c $(INC_CHECK) $(CFLAGS) $(LFLAGS) -lcheck tests.a -o $@
	./$@

gcov_report: tests
	gcovr -r . --html --html-details -o coverage_report.html
	rm -f tests_s21_string.gcda tests_s21_string.gcno
	#open coverage_report.html

linter:
	clang-format -i --style=Google ./backend/*.c ./backend/*.h ./frontend/*.c ./frontend/*.h ./tests_/*.c ./backend/stack/*.c ./backend/stack/*.h
	clang-format -n --style=Google ./backend/*.c ./backend/*.h ./frontend/*.c ./frontend/*.h ./tests_/*.c ./backend/stack/*.c ./backend/stack/*.h

clean: uninstall
	rm -rf *.dSYM unit_tests *.o *.out *.a html_report *.css *.html mid_html_res *.gcda *.gcno success fail test_results report tests test.c *.exe *.info *.gcov gcov_report/ ./docs *tar.gz

rebuild: clean all
