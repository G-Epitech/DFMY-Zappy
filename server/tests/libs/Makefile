##
## EPITECH PROJECT, 2024
## DFMY-Zappy
## File description:
## Makefile
##

clcc/libclcc.a:
	@make -C clcc

all: clcc/libclcc.a

clean:
	@make -C clcc clean

fclean:
	@make -C clcc fclean

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re clcc/libclcc.a
.DEFAULT_GOAL := all
