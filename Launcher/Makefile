##
## EPITECH PROJECT, 2023
## Title: Laplace Launcher v0.1.0
## Author: MasterLaplace
## Created: 2023-10-15
## File description:
## Makefile
##


NAME	= ../launcher

PYTHON	= python3

PIP		= pip3

all: install

install:
	@$(ECHO) $(BOLD) $(GREEN)"\n► INSTALL Launcher 📦 !\n"$(DEFAULT)
	@$(PYTHON) -m pip install --upgrade pip -q
	@$(PIP) freeze | grep -v moddb > ./requirements.txt 2> /dev/null
	@$(PIP) install -r ./requirements.txt -q
	@$(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE)" INSTALL Launcher 📦"$(DEFAULT)

lint:
	@$(PYTHON) -m pylint src/*.py

type:
	@$(PYTHON) -m mypy src/*.py

clean:
	@$(RM) __pycache__ .pytest_cache .mypy_cache
	@-$(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE)" CLEAN Launcher 💨"$(DEFAULT)

fclean: clean
	@$(RM) $(NAME)
	@-$(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE)" FCLEAN Launcher 🧻"$(DEFAULT)

re: clean all

## HELP MODE

help:
	@$(ECHO) $(BOLD) $(GREEN)"\n► LAUNCHER HELP 📖 !\n"$(DEFAULT)
	@$(ECHO) $(BOLD) $(LIGHT_BLUE)"► make install 📦 !"$(DEFAULT)
	@$(ECHO) $(BOLD) $(LIGHT_BLUE)"► make lint 📦 !"$(DEFAULT)
	@$(ECHO) $(BOLD) $(LIGHT_BLUE)"► make type 📦 !"$(DEFAULT)
	@$(ECHO) $(BOLD) $(LIGHT_BLUE)"► make clean 🧹 !"$(DEFAULT)
	@$(ECHO) $(BOLD) $(LIGHT_BLUE)"► make fclean 🧹 !"$(DEFAULT)
	@$(ECHO) $(BOLD) $(LIGHT_BLUE)"► make re 🧹 !"$(DEFAULT)
	@$(ECHO) $(BOLD) $(LIGHT_BLUE)"► make help: Show this help 📜"$(DEFAULT)
	@$(ECHO) $(BOLD) $(LIGHT_BLUE)"► make version: Show the version of the Laplace Launcher 📜 !"$(DEFAULT)

version:
	@$(ECHO) $(BOLD) $(GREEN)"\n► LAUNCHER VERSION 📜 !"$(DEFAULT)
	@$(ECHO) $(BOLD) $(LIGHT_BLUE)"\n► Laplace Launcher: $(shell cat VERSION)"$(DEFAULT)

.PHONY: all install lint type clean
