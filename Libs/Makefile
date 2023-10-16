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
SRC_LMAP 	=	$(wildcard LaplaceMap/*.c)
SRC_LLIB 	=	$(wildcard LaplaceLib/*.c)

SRC_TEST 	=	$(wildcard tests/*/*.c)

OBJ_LERROR 	=	$(SRC_LERROR:.c=.o)
OBJ_LLINK 	=	$(SRC_LLINK:.c=.o)
OBJ_LMAP 	=	$(SRC_LMAP:.c=.o)
OBJ_LLIB 	=	$(SRC_LLIB:.c=.o)

OBJ_TEST 	=	$(SRC_TEST:.c=.o)

INCLUDE_LERROR =	-I LaplaceError/include
INCLUDE_LLINK 	=	-I LaplaceLink/include
INCLUDE_LMAP 	=	-I LaplaceMap/include
INCLUDE_LLIB 	=	-I LaplaceLib/include

ifeq ($(OS), linux)
CC			=	gcc
NAME_LERROR =	libLaplaceError.a
NAME_LLINK 	=	libLaplaceLink.a
NAME_LMAP 	=	libLaplaceMap.a
NAME_LLIB 	=	libLaplaceLib.a
NAME_TEST 	=	unit_tests.out
endif
ifeq ($(OS), windows)
CC			=	x86_64-w64-mingw32-gcc
NAME_LERROR =	libLaplaceError.dll
NAME_LLINK 	=	libLaplaceLink.dll
NAME_LMAP 	=	libLaplaceMap.dll
NAME_LLIB 	=	libLaplaceLib.dll
NAME_TEST 	=	unit_tests.exe
endif
ifeq ($(OS), macos || $(OS), bsd)
CC			=	clang
NAME_LERROR =	libLaplaceError.dylib
NAME_LLINK 	=	libLaplaceLink.dylib
NAME_LMAP 	=	libLaplaceMap.dylib
NAME_LLIB 	=	libLaplaceLib.dylib
NAME_TEST 	=	unit_tests.out
endif

CFLAGS =	-Wall -Werror -Wpedantic $(INCLUDE_LLIB) $(INCLUDE_LLINK) $(INCLUDE_LMAP) $(INCLUDE_LERROR)
LDFLAGS =	-L. -lLaplaceLib -lLaplaceLink -lLaplaceMap -lLaplaceError
FASTFLAGS =	-Ofast -march=native -flto -fomit-frame-pointer \
			-fopenmp -fprefetch-loop-arrays -pipe

all:	$(NAME_LLIB) $(NAME_LLINK) $(NAME_LMAP) $(NAME_LERROR)

$(NAME_LERROR): SRC_COUNT := $(words $(SRC_LERROR))
$(NAME_LERROR):	$(OBJ_LERROR)
	@$(ECHO)
	@-($(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE) \
	"Lib LERROR sucessfully build ⛽."$(DEFAULT))
	@ar rc $(NAME_LERROR) $(OBJ_LERROR)

$(NAME_LLINK): 	SRC_COUNT := $(words $(SRC_LLINK))
$(NAME_LLINK):	$(OBJ_LLINK)
	@$(ECHO)
	@-($(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE) \
	"Lib LLINK sucessfully build ⛽."$(DEFAULT))
	@ar rc $(NAME_LLINK) $(OBJ_LLINK)

$(NAME_LMAP): 	SRC_COUNT := $(words $(SRC_LMAP))
$(NAME_LMAP):	$(OBJ_LMAP)
	@$(ECHO)
	@-($(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE) \
	"Lib LMAP sucessfully build ⛽."$(DEFAULT))
	@ar rc $(NAME_LMAP) $(OBJ_LMAP)

$(NAME_LLIB): 	SRC_COUNT := $(words $(SRC_LLIB))
$(NAME_LLIB):	$(OBJ_LLIB)
	@$(ECHO)
	@-($(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE) \
	"Lib LLIB sucessfully build ⛽."$(DEFAULT))
	@ar rc $(NAME_LLIB) $(OBJ_LLIB)

llib:	$(NAME_LLIB)
llink:	$(NAME_LLINK)
lmap:	$(NAME_LMAP)
lerror:	$(NAME_LERROR)

clean:
	@$(RM) $(OBJ_LERROR)
	@$(RM) $(OBJ_LLINK)
	@$(RM) $(OBJ_LMAP)
	@$(RM) $(OBJ_LLIB)
	@$(RM) $(OBJ_TEST)
	@-$(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE)" CLEAN LIBS 💨"$(DEFAULT)

fclean:	clean
	@$(RM) $(NAME_LERROR)
	@$(RM) $(NAME_LLINK)
	@$(RM) $(NAME_LMAP)
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
	@$(ECHO)
	@-($(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE) \
	"Lib TEST sucessfully build ⛽."$(DEFAULT))
	@./$(NAME_TEST)

%.o: %.c
	@$(eval NB=$(shell echo $$(($(NB)+1))))
	@-$(CC) -c -o $@ $< $(CFLAGS) $(LDFLAGS) $(FASTFLAGS) \
	&& python3 ../Scripts/improve_build.py $< $(NB) $(SRC_COUNT)

## HELP MODE

help:
	@$(ECHO) $(BOLD) $(GREEN)"\n► LIBS HELP 📜 !"$(DEFAULT)
	@$(ECHO) $(BOLD) $(LIGHT_BLUE)"► make llib: Build LaplaceLib Library 📚"$(DEFAULT)
	@$(ECHO) $(BOLD) $(LIGHT_BLUE)"► make llink: Build LaplaceLink Library 📚"$(DEFAULT)
	@$(ECHO) $(BOLD) $(LIGHT_BLUE)"► make lmap: Build LaplaceMap Library 📚"$(DEFAULT)
	@$(ECHO) $(BOLD) $(LIGHT_BLUE)"► make lerror: Build LaplaceError Library 📚"$(DEFAULT)
	@$(ECHO) $(BOLD) $(LIGHT_BLUE)"► make all: Build all Laplace Libraries 📚"$(DEFAULT)
	@$(ECHO) $(BOLD) $(LIGHT_BLUE)"► make clean: Clean all Laplace Libraries 🧹"$(DEFAULT)
	@$(ECHO) $(BOLD) $(LIGHT_BLUE)"► make fclean: Clean all Laplace Libraries 🧹"$(DEFAULT)
	@$(ECHO) $(BOLD) $(LIGHT_BLUE)"► make re: Clean all Laplace Libraries 🧹"$(DEFAULT)
	@$(ECHO) $(BOLD) $(LIGHT_BLUE)"► make debug: Build all Laplace Libraries in debug mode 🔧"$(DEFAULT)
	@$(ECHO) $(BOLD) $(LIGHT_BLUE)"► make gprof: Build all Laplace Libraries in gprof mode 🤖"$(DEFAULT)
	@$(ECHO) $(BOLD) $(LIGHT_BLUE)"► make tests_run: Build all Laplace Libraries in tests mode 🧪"$(DEFAULT)
	@$(ECHO) $(BOLD) $(LIGHT_BLUE)"► make help: Show this help 📜"$(DEFAULT)
	@$(ECHO) $(BOLD) $(LIGHT_BLUE)"► make version: Show the version of the Laplace Libraries 📜"$(DEFAULT)

version:
	@$(ECHO) $(BOLD) $(GREEN)"\n► LIBS VERSION 📜 !"$(DEFAULT)
	@$(ECHO) $(BOLD) $(LIGHT_BLUE)"\n► Laplace Library:$(shell cat VERSION)"$(DEFAULT)

.PHONY:	all clean fclean re debug tests_run
