##
## EPITECH PROJECT, 2024
## zappy_server
## File description:
## Makefile
##

zappy_server:
	@make -C server
	@ln -sf ./server/zappy_server zappy_server

zappy_ai:
	@ln -sf ./ai/zappy_ai zappy_ai

zappy_gui:
	@make -C graphic
	@echo "#! /bin/sh" > zappy_gui
	@printf "cd $(shell pwd)/graphic && ./zappy_gui $$%s\n" "@" >> zappy_gui
	@chmod +x zappy_gui

clean:
	@make -C graphic clean
	@make -C server clean

fclean:
	@make -C graphic fclean
	@make -C server fclean
	@rm -f *.log
	@rm -f zappy_server
	@rm -f zappy_ai
	@rm -f zappy_gui

tests_run:
	@make -C graphic tests_run
	@make -C server tests_run

all: zappy_server zappy_ai zappy_gui

.PHONY: all zappy_server zappy_ai zappy_gui tests_run clean fclean
.DEFAULT_GOAL := all
