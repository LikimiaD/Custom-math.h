CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11

all: custom_test_math gcov_report

test: custom_test_math

custom_math.o: custom_math.c
	$(CC) $(CFLAGS) -c $^ 

custom_math.a: custom_math.o
	ar rcs $@ $^

custom_test_math: custom_test_math.c custom_math.o custom_math.a
	$(CC) $(CFLAGS) $^ -o $@ -lm -lcheck
	./custom_test_math

gcov_report: custom_math.a
	$(CC) -c $(CFLAGS) --coverage custom_math.c
	$(CC) -c $(CFLAGS) custom_test_math.c
	$(CC) $(CFLAGS) *.o -o custom_test_math -lcheck -lm -lgcov
	./custom_test_math > report.txt || true
	lcov -o string_tests.info -c -d .
	genhtml -o report string_tests.info
	
clean:
	rm -f *.o test *.gcda *.gcno *.gcov *.info *.txt
	rm -rf report

.PHONY: all test clean gcov_report
