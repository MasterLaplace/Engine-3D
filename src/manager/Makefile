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
NAME :=	manager.out
else
CC := x86_64-w64-mingw32-gcc
NAME :=	manager.exe
endif

$(NAME): builder
	@$(CC) -Os -o $(NAME) manager.c \
	&& $(ECHO) $(BOLD) $(GREEN)"\n► BUILD MANAGER SUCCESS !"$(DEFAULT) \
	|| ($(ECHO) $(BOLD) $(RED)"\n► BUILD MANAGER FAILED"$(DEFAULT) && exit 1)

fclean:
	@$(RM) $(NAME)
	@$(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE)" FCLEAN MANAGER "$(DEFAULT)

all: fclean $(NAME)
