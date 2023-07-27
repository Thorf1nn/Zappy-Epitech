##
## EPITECH PROJECT, 2023
## zappy [WSL: Ubuntu]
## File description:
## Makefile
##

CC = gcc
CFLAGS = -W -Wall -Wextra -Werror -g3
CRFLAGS = --coverage -lcriterion
CPPFLAGS = -I./include

SRC = $(shell find . -name '*.c')
OBJ = $(SRC:.c=.o)

SRC_TESTS = $(wildcard args/*.c) \
			$(wildcard boards/*.c) \
			$(wildcard chained/*.c) \
			$(wildcard cmd/*.c) \
			$(wildcard cmd/commands/*.c) \
			$(wildcard output/*.c) \
			$(wildcard players/*.c) \
			$(wildcard server/*.c) \
			$(wildcard server/handle/*.c) \
			$(wildcard server/networks/*.c) \
			$(wildcard utils/*.c) \
			$(wildcard ../../tests_c/*.c)

OBJ_TEST = $(SRC_TEST:.c=.o)

BIN = zappy_server
UNIT_TEST = unit_tests_c
$(shell ./python/proto)

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) -o $(BIN) $(OBJ)
	cp $(BIN) ../../

clean:
	$(RM) $(OBJ)
	$(RM) *.gcno
	$(RM) *.gcda

fclean: clean
	$(RM) ../../$(BIN)
	$(RM) ./$(BIN)
	$(RM) $(UNIT_TEST)

re: fclean all

$(UNIT_TEST):
	$(CC) -o $(UNIT_TEST) $(SRC_TESTS) $(CPPFLAGS) $(CRFLAGS)

tests_run: $(UNIT_TEST)
	@echo "\033[1;91m\n=====| Unit Tests C:\033[0m"
	./$(UNIT_TEST)
