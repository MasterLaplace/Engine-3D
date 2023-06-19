##
## EPITECH PROJECT, 2023
## Laplace Library v1.0.0
## File description:
## Makefile
##

-include .env
export

SRC_MY =	$(wildcard my/*.c)
SRC_LINK =	$(wildcard link/*.c)

SRC_TEST =	$(wildcard tests/*/*.c)

OBJ_MY =	$(SRC_MY:.c=.o)
OBJ_LINK =	$(SRC_LINK:.c=.o)

OBJ_TEST =	$(SRC_TEST:.c=.o)

NAME_MY =	libmy.a
NAME_LINK =	liblink.a

NAME_TEST =	unit_tests

INCLUDE_MY =	-I my/include
INCLUDE_LINK =	-I link/include

CC =	gcc

CFLAGS =	-Wall -Werror -Wpedantic $(INCLUDE_MY) $(INCLUDE_LINK)
LDFLAGS =	-L. -lmy -llink
FASTFLAGS =	-Ofast -march=native -flto -fomit-frame-pointer \
			-fopenmp -fprefetch-loop-arrays -pipe

SRC_COUNT := $(words $(SRC))
NB = 0

all:	$(NAME_MY) $(NAME_LINK)

$(NAME_MY):		$(OBJ_MY)
	@$(ECHO)
	@-($(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE) \
	"Lib MY sucessfully build ⛽."$(DEFAULT))
	@ar rc $(NAME_MY) $(OBJ_MY)

$(NAME_LINK):	$(OBJ_LINK)
	@$(ECHO)
	@-($(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE) \
	"Lib LINK sucessfully build ⛽."$(DEFAULT))
	@ar rc $(NAME_LINK) $(OBJ_LINK)

my:		$(NAME_MY)
link:	$(NAME_LINK)

clean:
	@$(RM) $(OBJ_MY)
	@$(RM) $(OBJ_LINK)
	@$(RM) $(OBJ_TEST)
	@find -type f -name "*.gcda" -delete
	@find -type f -name "*.gcno" -delete
	@-$(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE)" CLEAN LIB 💨"$(DEFAULT)

fclean:	clean
	@$(RM) $(NAME_MY)
	@$(RM) $(NAME_LINK)
	@$(RM) $(NAME_TEST)
	@$(RM) *.gcda
	@$(RM) *.gcno
	@-$(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE)" FCLEAN LIB 🧻"$(DEFAULT)

re:	fclean all

debug:	CFLAGS += -g3 -ggdb
debug:	FASTFLAGS = -Og -pipe
debug:	re

gprof:	CFLAGS += -pg
gprof:	re

tests_run:	CFLAGS += --coverage -lcriterion -Wno-deprecated-declarations
tests_run:	re $(OBJ_TEST)
	@$(CC) -o $(NAME_TEST) $(OBJ_TEST) $(CFLAGS) $(LDFLAGS) $(FASTFLAGS)
	@./$(NAME_TEST)
	@gcovr --exclude tests/
	@gcovr --exclude tests/ --branches

%.o: %.c
	@$(eval NB=$(shell echo $$(($(NB)+1))))
	@-$(CC) -c -o $@ $< $(CFLAGS) $(LDFLAGS) $(FASTFLAGS) \
	&& python3 ../build/build.py $< $(NB) $(SRC_COUNT)

.PHONY:	all clean fclean re debug tests_run
