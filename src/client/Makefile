##
## EPITECH PROJECT, 2023
## Engine-3D
## File description:
## Makefile
##

-include .env
export

builder:
ifeq ($(OS), linux)
CC := gcc
NAME :=	client.out
else
CC := x86_64-w64-mingw32-gcc
NAME :=	client.exe
endif

NO_CFLAGS = -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable -Wno-unused-function -Wno-unused-result -Wno-missing-field-initializers -Wno-missing-braces

CFLAGS = $(FLAGS) -I ../../includes -I ./includes -I /usr/include/python3.9 -g3 -ggdb -fPIC

PYFLAGS = -lpython3.9

SHARED_ENGINE = -L ./bin/  -lengine

CSFML_F		=	-l csfml-graphics -l csfml-system -l csfml-window -l csfml-audio -lm

LIB = -L ../../lib/ -lmy

$(NAME): builder
	@$(CC) -Os $(CFLAGS) -o $(NAME) client.c -lpthread $(PYFLAGS) $(CSFML_F) $(SHARED_ENGINE) $(LIB) \
	&& $(ECHO) $(BOLD) $(GREEN)"\n► BUILD CLIENT SUCCESS !"$(DEFAULT) \
	|| ($(ECHO) $(BOLD) $(RED)"\n► BUILD CLIENT FAILED"$(DEFAULT) && exit 1)
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./bin/
	export LD_LIBRARY_PATH

fclean:
	@$(RM) $(NAME)
	@($(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE)" FCLEAN CLIENT "$(DEFAULT))

all: fclean $(NAME)
