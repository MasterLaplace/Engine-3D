##
## EPITECH PROJECT, 2023
## Laplace Library v1.0.0
## File description:
## Makefile
##

-include .env
export

SRC_LERROR =	$(wildcard lerror/*.c)
SRC_LINK =	$(wildcard link/*.c)
SRC_MY =	$(wildcard my/*.c)

SRC_TEST =	$(wildcard tests/*/*.c)

OBJ_LERROR =	$(SRC_LERROR:.c=.o)
OBJ_LINK =	$(SRC_LINK:.c=.o)
OBJ_MY =	$(SRC_MY:.c=.o)

OBJ_TEST =	$(SRC_TEST:.c=.o)

# NAME =		liblaplace.a
# NAME_LEXER =	liblexer.a
# NAME_PARSER =	libparser.a
NAME_LERROR =	liblerror.a
NAME_LINK =	liblink.a
NAME_MY =	libmy.a

# override NB := 0

NB_LERROR := 0
NB_LINK := 0
NB_MY := 0
NAME_TEST =	unit_tests

INCLUDE_LERROR =	-I lerror/include
INCLUDE_LINK =	-I link/include
INCLUDE_MY =	-I my/include

CC =	gcc

CFLAGS =	-Wall -Werror -Wpedantic $(INCLUDE_MY) $(INCLUDE_LINK) $(INCLUDE_LERROR)
LDFLAGS =	-L. -lmy -llink
FASTFLAGS =	-Ofast -march=native -flto -fomit-frame-pointer \
			-fopenmp -fprefetch-loop-arrays -pipe

all:	$(NAME_MY) $(NAME_LINK) $(NAME_LERROR)

$(NAME_LERROR): SRC_COUNT := $(words $(SRC_LERROR))
$(NAME_LERROR):	$(OBJ_LERROR)
	@$(eval NB_LERROR=$(shell echo $$(($(NB_LERROR)+1))))
	@$(ECHO)
	@-($(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE) \
	"Lib LERROR sucessfully build ⛽."$(DEFAULT))
	@ar rc $(NAME_LERROR) $(OBJ_LERROR)

$(NAME_LINK): SRC_COUNT := $(words $(SRC_LINK))
$(NAME_LINK):	$(OBJ_LINK)
	@$(eval NB_LINK=$(shell echo $$(($(NB_LINK)+1))))
	@$(ECHO)
	@-($(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE) \
	"Lib LINK sucessfully build ⛽."$(DEFAULT))
	@ar rc $(NAME_LINK) $(OBJ_LINK)

$(NAME_MY): SRC_COUNT := $(words $(SRC_MY))
$(NAME_MY):		$(OBJ_MY)
	@$(ECHO)
	@-($(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE) \
	"Lib MY sucessfully build ⛽."$(DEFAULT))
	@ar rc $(NAME_MY) $(OBJ_MY)

my:		$(NAME_MY)
link:	$(NAME_LINK)

clean:
	@$(RM) $(OBJ_LERROR)
	@$(RM) $(OBJ_LINK)
	@$(RM) $(OBJ_MY)
	@$(RM) $(OBJ_TEST)
	@find -type f -name "*.gcda" -delete
	@find -type f -name "*.gcno" -delete
	@-$(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE)" CLEAN LIB 💨"$(DEFAULT)

fclean:	clean
	@$(RM) $(NAME_LERROR)
	@$(RM) $(NAME_LINK)
	@$(RM) $(NAME_MY)
	@$(RM) $(NAME_TEST)
	@$(RM) *.gcda
	@$(RM) *.gcno
	@-$(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE)" FCLEAN LIB 🧻"$(DEFAULT)

re:	fclean all

debug:	CFLAGS += -g3 -ggdb
debug:	FASTFLAGS = -Og -pipe
debug:	re

gprof:	CFLAGS += -pg
gprof:	FASTFLAGS += -fno-omit-frame-pointer
gprof:	re

tests_run:	CFLAGS += --coverage -lcriterion -Wno-deprecated-declarations
tests_run:	re $(OBJ_TEST)
	@$(CC) -o $(NAME_TEST) $(OBJ_TEST) $(CFLAGS) $(LDFLAGS) $(FASTFLAGS)
	@./$(NAME_TEST)

%.o: %.c
	@$(eval NB=$(shell echo $$(($(NB)+1))))
	@-$(CC) -c -o $@ $< $(CFLAGS) $(LDFLAGS) $(FASTFLAGS) \
	&& python3 ../build/build.py $< $(NB) $(SRC_COUNT)

.PHONY:	all clean fclean re debug tests_run
