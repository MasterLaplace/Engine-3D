##
## EPITECH PROJECT, 2023
## Title: Laplace Libraries v1.0.0
## Author: MasterLaplace
## Created: 2023-10-13
## File description:
## Makefile
##

-include .env
export

SRC_LERROR 	=	$(wildcard LaplaceError/*.c)
SRC_LLINK 	=	$(wildcard LaplaceLink/*.c)
SRC_LLIB 	=	$(wildcard LaplaceLib/*.c)

SRC_TEST 	=	$(wildcard tests/*/*.c)

OBJ_LERROR 	=	$(SRC_LERROR:.c=.o)
OBJ_LLINK 	=	$(SRC_LLINK:.c=.o)
OBJ_LLIB 	=	$(SRC_LLIB:.c=.o)

OBJ_TEST 	=	$(SRC_TEST:.c=.o)

NAME_LERROR =	libLaplaceError.a
NAME_LLINK 	=	libLaplaceLink.a
NAME_LLIB 	=	libLaplaceLib.a
NAME_TEST 	=	unit_tests.out

NB_LERROR 	:= 0
NB_LLINK 	:= 0
NB_LLIB 	:= 0
NB_TEST 	:= 0

INCLUDE_LERROR =	-I LaplaceError/include
INCLUDE_LLINK 	=	-I LaplaceLink/include
INCLUDE_LLIB 	=	-I LaplaceLib/include

CC =	gcc

CFLAGS =	-Wall -Werror -Wpedantic $(INCLUDE_LLIB) $(INCLUDE_LLINK) $(INCLUDE_LERROR)
LDFLAGS =	-L. -lLaplaceLib -lLaplaceLink
FASTFLAGS =	-Ofast -march=native -flto -fomit-frame-pointer \
			-fopenmp -fprefetch-loop-arrays -pipe

all:	$(NAME_LLIB) $(NAME_LLINK) $(NAME_LERROR)

$(NAME_LERROR): SRC_COUNT := $(words $(SRC_LERROR))
$(NAME_LERROR):	$(OBJ_LERROR)
	@$(eval NB_LERROR=$(shell echo $$(($(NB_LERROR)+1))))
	@$(ECHO)
	@-($(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE) \
	"Lib LERROR sucessfully build ⛽."$(DEFAULT))
	@ar rc $(NAME_LERROR) $(OBJ_LERROR)

$(NAME_LLINK): 	SRC_COUNT := $(words $(SRC_LLINK))
$(NAME_LLINK):	$(OBJ_LLINK)
	@$(eval NB_LLINK=$(shell echo $$(($(NB_LLINK)+1))))
	@$(ECHO)
	@-($(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE) \
	"Lib LLINK sucessfully build ⛽."$(DEFAULT))
	@ar rc $(NAME_LLINK) $(OBJ_LINK)

$(NAME_LLIB): 	SRC_COUNT := $(words $(SRC_LLIB))
$(NAME_LLIB):	$(OBJ_LLIB)
	@$(eval NB_LLIB=$(shell echo $$(($(NB_LLIB)+1))))
	@$(ECHO)
	@-($(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE) \
	"Lib LLIB sucessfully build ⛽."$(DEFAULT))
	@ar rc $(NAME_LLIB) $(OBJ_LLIB)

llib:	$(NAME_LLIB)
llink:	$(NAME_LLINK)

clean:
	@$(RM) $(OBJ_LERROR)
	@$(RM) $(OBJ_LLINK)
	@$(RM) $(OBJ_LLIB)
	@$(RM) $(OBJ_TEST)
	@-$(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE)" CLEAN LIBS 💨"$(DEFAULT)

fclean:	clean
	@$(RM) $(NAME_LERROR)
	@$(RM) $(NAME_LLINK)
	@$(RM) $(NAME_LLIB)
	@$(RM) $(NAME_TEST)
	@find -type f -name "*.gcda" -delete
	@find -type f -name "*.gcno" -delete
	@-$(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE)" FCLEAN LIBS 🧻"$(DEFAULT)

re:	fclean all

debug:	CFLAGS += -g3 -ggdb
debug:	FASTFLAGS = -Og -pipe
debug:	re

gprof:	CFLAGS += -pg
gprof:	FASTFLAGS += -fno-omit-frame-pointer
gprof:	re

tests_run:	CFLAGS += --coverage -lcriterion -Wno-deprecated-declarations
tests_run: 	SRC_COUNT := $(words $(SRC_TEST))
tests_run:	re $(OBJ_TEST)
	@$(CC) -o $(NAME_TEST) $(OBJ_TEST) $(CFLAGS) $(LDFLAGS) $(FASTFLAGS)
	@$(eval NB_TEST=$(shell echo $$(($(NB_TEST)+1))))
	@$(ECHO)
	@-($(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE) \
	"Lib TEST sucessfully build ⛽."$(DEFAULT))
	@./$(NAME_TEST)

%.o: %.c
	@$(eval NB=$(shell echo $$(($(NB)+1))))
	@-$(CC) -c -o $@ $< $(CFLAGS) $(LDFLAGS) $(FASTFLAGS) \
	&& python3 ../Scripts/improve_build.py $< $(NB) $(SRC_COUNT)

.PHONY:	all clean fclean re debug tests_run
