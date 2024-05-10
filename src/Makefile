FLAGS = -std=c++17 -Wall -Werror -Wextra
TEST = tests/tests.cc
GCOV_FLAGS = -ftest-coverage -fprofile-arcs
TEST_FLAGS = -lgtest -lpthread
LINUX_TEST_PATH = -I/usr/include/gtest

all: s21_matrix_oop.a

s21_matrix_oop.a: s21_matrix_oop.cc
	g++ $(FLAGS) -c $<
	ar rc $@ *.o
	ranlib $@
	

test: rebuild s21_matrix_oop.a
	g++ $(FLAGS) $(TEST) s21_matrix_oop.a $(LINUX_TEST_PATH) $(TEST_FLAGS) -o $@
	./test

gcov_report: rebuild
	g++ $(FLAGS) -c $(TEST) 
	g++ $(FLAGS) $(GCOV_FLAGS) -c *.cc 
	g++ $(FLAGS) $(GCOV_FLAGS) *.o $(TEST_FLAGS) -o gcovreport 
	./gcovreport
	lcov -t "gcovreport" -o gcovreport.info -c -d . --exclude "v1/*" 
	genhtml -o report gcovreport.info
	open report/./index.html

rebuild:
	$(MAKE) clean 
	$(MAKE) all

clean: 
	rm -rf test *.o *.a *.gcda *.gcno gcovreport* report Dockerfile

docker_valgrind:
	@echo "FROM ubuntu:latest" > Dockerfile
	@echo "RUN apt-get update && apt-get install -y \\" >> Dockerfile
	@echo "g++ \\" >> Dockerfile
	@echo "make \\" >> Dockerfile
	@echo "valgrind \\" >> Dockerfile
	@echo "googletest \\" >> Dockerfile
	@echo "libgtest-dev" >> Dockerfile
	@echo "WORKDIR /app " >> Dockerfile
	@echo "COPY . /app" >> Dockerfile
	@echo "RUN	make test" >> Dockerfile
	@echo "CMD ["bash"]" >> Dockerfile
	docker build -t myproject .
	docker run --rm myproject valgrind --leak-check=full --show-leak-kinds=all ./test
	rm -f Dockerfile