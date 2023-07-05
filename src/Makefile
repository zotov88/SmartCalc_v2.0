CC = g++ -g
FLAGS = -Wall -Werror -Wextra --std=c++17 -pedantic
FLAGS_CHECK= -lgtest_main -lgtest -pthread -lgcov -fprofile-arcs -ftest-coverage
SOURCES= test
OBJECTS=$(SOURCES:.c=.o)
TEST_FILES= tests/test.cc
MODEL= calculator/model/model.cc calculator/controller/controller.cc 

all: uninstall install gcov_report

install: build_dir
	cd calculator && qmake && make && make clean && rm Makefile && cd .. && mv calculator/calculator build

uninstall:
	rm -rf build

test: 
	@rm -rf tests-out
	@mkdir tests-out
	$(CC) $(FLAGS) $(TEST_FILES) $(MODEL) ${FLAGS_CHECK} -o tests-out/test -g 
	@./tests-out/test

add_coverage_flag:
	$(eval CFLAGS += --coverage)

gcov_report:
	@rm -rf report
	@mkdir report
	$(CC) --coverage $(TEST_FILES) $(MODEL) ${FLAGS} ${FLAGS_CHECK} -o report/main
	@./report/main
	@lcov -t "main" -o report/main.info -c -d ./ --exclude '/usr/include/*'
	@genhtml -o report report/main.info
	@rm report/*.gcda report/*.gcno
	@open report/index.html

clean:
	@rm -rf build-calculator-Qt6-Debug html latex build report tests-out *.txt *.tar

dvi:
	@doxygen doxy/Doxyfile
	@open ./html/index.html

dist: clean install
	@rm -rf dist.tar
	@tar  -cvzf dist.tar build
	make uninstall

build_dir:
	@rm -rf build
	@mkdir build

rebuild:
	make clean
	make all

leak: clean test
	@valgrind --leak-check=full --show-reachable=yes --show-leak-kinds=all --track-origins=yes --log-file=out_valgrind.txt ./tests-out/test
	@rm -rf tests-out

git:
	@git add .
	@git commit -m "$(c)"
	@git push
