CC = gcc
CFLAGS = -Wall -Wextra -pedantic -O0 -g --coverage
LDFLAGS = --coverage

TARGET = qsort
SRCS = qsort.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean test coverage

all: $(TARGET)

$(TARGET): $(OBJS)
  $(CC) $(LDFLAGS) $^ -o $@

%.o: %.c
  $(CC) $(CFLAGS) -c $< -o $@

clean:
  rm -f $(OBJS) $(TARGET) *.gcov *.gcda *.gcno coverage.info -r html

test:
  ./$(TARGET) < test1.txt;\
	./$(TARGET) < test2.txt;\
	./$(TARGET) < test3.txt;\
	./$(TARGET) < test4.txt;\
	./$(TARGET) < test5.txt;\
	./$(TARGET) < test6.txt;\
	./$(TARGET) < test7.txt;\
	./$(TARGET) < test8.txt;\

coverage: test
  lcov --rc lcov_branch_coverage=1 -c -d . -o coverage.info
	genhtml --branch-coverage coverage.info -o html	
	  

