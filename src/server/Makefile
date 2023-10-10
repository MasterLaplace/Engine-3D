##
## EPITECH PROJECT, 2023
## Engine-3D
## File description:
## Makefile
##

-include .env
export

ifeq ($(OS), linux)
CC := gcc
NAME :=	server.out
else
CC := x86_64-w64-mingw32-gcc
NAME :=	server.exe
endif


INCLUDES	=	-I ./includes -I ./includes \
				-I ../../libs/my/include -I ../../libs/link/include

LIB_NAME	=	-L ../../libs -lmy -llink

LDFLAGS		=	$(INCLUDES) $(LIB_NAME) -lpthread

$(NAME):
	@$(CC) -Os -o $(NAME) server.c $(LDFLAGS) \
	&& $(ECHO) $(BOLD) $(GREEN)"\n► BUILD SERVER SUCCESS !"$(DEFAULT) \
	|| ($(ECHO) $(BOLD) $(RED)"\n► BUILD SERVER FAILED"$(DEFAULT) && exit 1)

fclean:
	@$(RM) $(NAME)
	@$(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE)" FCLEAN SERVER "$(DEFAULT)

all: fclean $(NAME)
