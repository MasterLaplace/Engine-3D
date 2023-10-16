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
	@$(PIP) freeze | grep -v moddb > ./requirements.txt
	@$(PIP) install -r ./requirements.txt

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

.PHONY: all install lint type clean
