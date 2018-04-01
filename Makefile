SHELL = /bin/sh

# Where the files are
COMMON_DIR = ./src/
TEST_DIR = ./tests/

EXECUTABLE_NAME = befungi
TEST_NAME = test

INSTALL_DIR = /usr/local/bin/
INSTALL_COMMAND = install


COMMON_FILES = state.o fungi.o
TEST_FILES = main.o state.o fungi.o
NOTEST_FILES = main.o

COMMON_SOURCES = $(COMMON_FILES:%.o=$(COMMON_DIR)/%.o)
TEST_SOURCES = $(TEST_FILES:%.o=$(TEST_DIR)/%.o)
NOTEST_SOURCES = $(NOTEST_FILES:%.o=$(COMMON_DIR)/%.o)

# Compiler flags
CPPFLAGS = -std=c++14 -Wall -Wextra -pedantic -I$(COMMON_DIR)

# Build recipe
befungi: $(COMMON_SOURCES) $(NOTEST_SOURCES)
	$(CXX) -o $(EXECUTABLE_NAME) $(NOTEST_SOURCES) $(COMMON_SOURCES) $(CPPFLAGS)
test: $(COMMON_SOURCES) $(TEST_SOURCES)
	$(CXX) -o $(TEST_NAME) $(TEST_SOURCES) $(COMMON_SOURCES) $(CPPFLAGS)
	./test
install:
	$(INSTALL_COMMAND) $(EXECUTABLE_NAME) $(INSTALL_DIR)
uninstall:
	rm $(INSTALL_DIR)/$(EXECUTABLE_NAME)
clean:
	rm -f *.o
	rm -f $(COMMON_SOURCES)/*.o
	rm -f $(TEST_SOURCES)/*.o
	rm -f $(TEST_NAME)
	rm -f $(EXECUTABLE_NAME)

