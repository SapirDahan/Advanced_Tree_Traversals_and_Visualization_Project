# * Author: Sapir Dahan
# * ID: 325732972
# * Mail: sapirdahan2003@gmail.com

CXX=g++
CXXFLAGS=-std=c++17 -Werror -Wsign-conversion
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all --error-exitcode=99

# SFML library flags
SFML_LIBS=-lsfml-graphics -lsfml-window -lsfml-system

# Source files
SOURCES=Demo.cpp tree.cpp gui.cpp Complex.cpp
OBJECTS=$(subst .cpp,.o,$(SOURCES))

# Test files
TEST_SOURCES=Tests.cpp TestCounter.cpp Complex.cpp tree.cpp gui.cpp
TEST_OBJECTS=$(subst .cpp,.o,$(TEST_SOURCES))

run: tree
	./$^

tree: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o tree $(SFML_LIBS)

test: $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o test -pthread $(SFML_LIBS)

# tidy:
#	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

# Using cppcheck instead of tidy, since I use g++ compiler which is better suited for my machine
cppcheck:
	cppcheck $(SOURCES) --enable=all

valgrind: tree
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./tree 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o test tree
