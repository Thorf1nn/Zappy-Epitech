##
## EPITECH PROJECT, 2023
## B-YEP-400-MPL-4-1-zappy-hugo.eschlimann
## File description:
## Makefile
##

SRC = main.py

BIN = zappy_ai

all:
	cp $(SRC) $(BIN)
	chmod +x $(BIN)
	mv $(BIN) ../../

clean:
	$(RM) ../../$(BIN)

fclean: clean

re: fclean all

tests_run:
	@echo "\033[1;91m\n=====| Unit Tests Python:\033[0m"
	python3 test_parsing.py
