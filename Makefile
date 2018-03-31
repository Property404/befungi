SHELL = /bin/sh

# Where the files are
COMMON_DIR = ./src/
TEST_DIR = ./tests/

EXECUTABLE_NAME = befungi
TEST_NAME = test

# Compiler flags
CC = g++ # More portable than using 'gcc,' but with risk
	# of calling wrong compiler
CFLAGS = -Wall -Wextra -pedantic -std=c++14

COMMON_FILES = state.o fungi.o
TEST_FILES = main.o state.o fungi.o
NOTEST_FILES = main.o

COMMON_SOURCES = $(COMMON_FILES:%.o=$(COMMON_DIR)/%.o)
TEST_SOURCES = $(TEST_FILES:%.o=$(TEST_DIR)/%.o)
NOTEST_SOURCES = $(NOTEST_FILES:%.o=$(COMMON_DIR)/%.o)

# Build recipe
befungi: $(COMMON_SOURCES) $(NOTEST_SOURCES)
	$(CC) -o $(EXECUTABLE_NAME) $(NOTEST_SOURCES) $(COMMON_SOURCES) $(CFLAGS)
test: $(COMMON_SOURCES) $(TEST_SOURCES)
	$(CC) -o $(TEST_NAME) $(TEST_SOURCES) $(COMMON_SOURCES) $(CFLAGS)
	./test
clean:
	rm -f *.o
	rm -f $(COMMON_SOURCES)/*.o
	rm -f $(TEST_SOURCES)/*.o
	rm -f $(TEST_NAME)
	rm -f $(EXECUTABLE_NAME)

