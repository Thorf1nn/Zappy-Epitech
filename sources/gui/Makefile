##
## EPITECH PROJECT, 2023
## B-YEP-400-MPL-4-1-zappy-hugo.eschlimann
## File description:
## Makefile
##

CXX = g++ -g3 -std=c++2a -I./window -I./utils -I./map -I./texture -I./mesh -I./models -I./text -I./animation -I./server -I./parser -I./exceptions -I./music
CXXFLAGS = -W -Wall -Wextra
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -fno-gnu-unique
CRFLAGS = --coverage -lcriterion

SRC	=	$(shell find . -name "*.cpp")
SRC_TESTS =	$(wildcard animation/*.cpp) \
			$(wildcard core/*.cpp) \
			$(wildcard graphic/*.cpp) \
			$(wildcard map/*.cpp) \
			$(wildcard mesh/*.cpp) \
			$(wildcard models/*.cpp) \
			$(wildcard music/*.cpp) \
			$(wildcard parser/*.cpp) \
			$(wildcard server/*.cpp) \
			$(wildcard text/*.cpp) \
			$(wildcard texture/*.cpp) \
			$(wildcard utils/*.cpp) \
			$(wildcard window/*.cpp) \
		    $(shell find ../../tests_cpp/ -name "*.cpp")

OBJ = $(SRC:.cpp=.o)
OBJ_TEST = $(SRC:.cpp=.o)

BIN = zappy_gui
UNIT_TEST = unit_tests_cpp


all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) -o $(BIN) $(OBJ) $(LDFLAGS)
	mv $(BIN) ../../

clean:
	$(RM) $(OBJ)
	$(RM) *.gcno
	$(RM) *.gcda

fclean: clean
	$(RM) ../../$(BIN)
	$(RM) $(UNIT_TEST)

re: fclean all

$(UNIT_TEST):
	$(CXX) -o $(UNIT_TEST) $(SRC_TESTS) $(LDFLAGS) $(CRFLAGS)

tests_run: $(UNIT_TEST)
	@echo "\033[1;91m\n=====| Unit Tests Cpp:\033[0m"
	./$(UNIT_TEST)
