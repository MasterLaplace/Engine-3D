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

$(NAME): builder
	@$(CC) -Os -o $(NAME) client.c -I ./includes -lpthread \
	&& $(ECHO) $(BOLD) $(GREEN)"\n► BUILD CLIENT SUCCESS !"$(DEFAULT) \
	|| ($(ECHO) $(BOLD) $(RED)"\n► BUILD CLIENT FAILED"$(DEFAULT) && exit 1)

fclean:
	@$(RM) $(NAME)
	@($(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE)" FCLEAN CLIENT "$(DEFAULT))

all: fclean $(NAME)
