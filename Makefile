UNIT_TEST = unit_tests

all:
	make -C sources/client/
	make -C sources/server/
	make -C sources/gui/

zappy_server:
	make -C sources/server/

zappy_ai:
	make -C sources/client/

zappy_gui:
	make -C sources/gui/

clean:
	make -C sources/client/ clean
	make -C sources/server/ clean
	make -C sources/gui/ clean

fclean:
	make -C sources/client/ fclean
	make -C sources/server/ fclean
	make -C sources/gui/ fclean

re:
	make -C sources/client/ re
	make -C sources/server/ re
	make -C sources/gui/ re

$(UNIT_TEST):
	make -C sources/server/ unit_tests_c
	make -C sources/gui/ unit_tests_cpp

tests_run:
	make -C sources/server/ tests_run
	make -C sources/gui/ tests_run
	make -C sources/client/ tests_run
