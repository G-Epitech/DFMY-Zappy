##
## EPITECH PROJECT, 2024
## DFMY-Zappy
## File description:
## Makefile
##

NAME 		= zappy_server
TESTS_NAME 	= zappy_server_tests
BUILD_PATH 	= build
COVERAGE_IGNORE_TARGETS = 	tests \

COVERAGE_IGNORE = $(addprefix -e , $(COVERAGE_IGNORE_TARGETS))

ifdef DEBUG
	CMAKE_FLAGS = -DCMAKE_BUILD_TYPE=Debug
else
	CMAKE_FLAGS = -DCMAKE_BUILD_TYPE=Release
endif

all:		$(NAME)

$(NAME):
			@cmake -S . -B $(BUILD_PATH) $(CMAKE_FLAGS)
			@cmake --build $(BUILD_PATH) --target $(NAME)

clean:
			@rm -rf $(BUILD_PATH)

fclean:		clean
			@rm -f ../$(NAME)
			@rm -f ../$(TESTS_NAME)
			@rm -rf cmake-build-*
			@rm -rf build
			@rm -rf *.log

re:
			@$(MAKE) fclean
			@$(MAKE) all

tests_run:	fclean
			@$(MAKE) -C tests/libs
			@cmake -S . -B $(BUILD_PATH) -DCOVERAGE=ON
			@cmake --build $(BUILD_PATH) --target $(TESTS_NAME)
			@./../$(TESTS_NAME) -j1

coverage:
			@gcovr $(COVERAGE_IGNORE)

coverage-branch:
			@gcovr $(COVERAGE_IGNORE) --branch

.PHONY: all clean fclean re tests_run coverage coverage-branch $(NAME)

DEFAULT_GOAL := all
