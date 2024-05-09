FLAGS = -std=c++17 -Wall -Werror -Wextra
TEST = tests/tests.cc
GCOV = -ftest-coverage -fprofile-arcs

all: s21_matrix_oop.a

s21_matrix_oop.a: s21_matrix_oop.cc
	g++ $(FLAGS) -c $<
	ar rc $@ *.o
	ranlib $@
	

test: rebuild s21_matrix_oop.a
	g++ $(FLAGS) $(TEST) s21_matrix_oop.a -lgtest -lpthread -o $@
	./test

gcov_report: rebuild
	g++ $(FLAGS) -c $(TEST) 
	g++ $(FLAGS) $(GCOV)  -c *.cc 
	g++ $(FLAGS) $(GCOV) *.o -lgtest -lpthread  -o gcovreport 
	./gcovreport
	lcov -t "gcovreport" -o gcovreport.info -c -d .
	genhtml -o report gcovreport.info
	open report/./index.html

rebuild:
	$(MAKE) clean 
	$(MAKE) all

clean: 
	rm -rf test *.o *.a *.gcda *.gcno gcovreport* report