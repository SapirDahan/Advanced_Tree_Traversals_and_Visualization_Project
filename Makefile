#
# * Author: Sapir Dahan
# * ID: 325732972
# * Mail: sapirdahan2003@gmail.com
#

#!make -f

CXX=g++
CXXFLAGS=-std=c++17 -Werror -Wsign-conversion
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all --error-exitcode=99

SOURCES=main.cpp
OBJECTS=$(subst .cpp,.o,$(SOURCES))

run: tree
	./$^

tree: Demo.o
	$(CXX) $(CXXFLAGS) $^ -o tree

test: TestCounter.o Tests.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o test

# tidy:
#	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

# Using cppcheck instead of tidy, since I use g++ compiler which is better suited for my machine
cppcheck:
	cppcheck $(SOURCES) --enable=all

valgrind: tree
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f *.o test tree
