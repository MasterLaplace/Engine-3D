##
## ME PROJECT, 2022
## DEN-GINER-Master-Laplace
## File description:
## Makefile
##

-include .env
export

SRC_DIR 	= 	src/

TEST_DIR 	= 	test/

BIN 		=	bin/

SRC		=   $(SRC_DIR)init.c		\
			$(SRC_DIR)clean.c		\
			$(SRC_DIR)parser_obj.c 	\

TEST	=	$(TEST_DIR)test.c

builder:
ifeq ($(OS), linux)
CC := gcc
else
CC := x86_64-w64-mingw32-gcc
endif

MAIN		=	$(SRC_DIR)core.c

OBJ			=	$(SRC:.c=.o) $(MAIN:.c=.o)

TEST_OBJ	=	$(SRC:.c=.o) $(TEST:.c=.o)

NAME		=	$(BIN)engine

SHARE_NAME = 	$(BIN)engine.so

TEST_NAME 	=	$(BIN)test_engine

INCLUDE 	=	./includes

LIB_FOLDER	=	./lib

LIB_NAME	=	my

LDFLAGS		=	-L $(LIB_FOLDER) -l $(LIB_NAME) -lm

CFLAGS		=	$(FLAGS) -I $(INCLUDE)

TEST_FLAGS	=	-I ./test

CSFML_F		=	-l csfml-graphics -l csfml-system -l csfml-window -l csfml-audio

SRC_COUNT 	:= 	$(words $(SRC))
NB 	= 0

$(NAME): $(OBJ)
	@make -C $(LIB_FOLDER) $(NO_PRINT)
	@$(CC) -Os $(FLAGS) -o $(NAME) $(OBJ) $(LDFLAGS) $(CSFML_F) \
	&& $(ECHO) $(BOLD) $(GREEN)"\n► BUILD SUCCESS !"$(DEFAULT) \
	|| ($(ECHO) $(BOLD) $(RED)"\n► BUILD FAILED"$(DEFAULT) && exit 1)

all: $(NAME)

clean:
	@$(RM) $(OBJ)
	@$(RM) $(TEST_OBJ)
	@make -C $(LIB_FOLDER) clean $(NO_PRINT)
	@$(RM) *~
	@$(RM) *#
	@($(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE)" CLEAN "$(DEFAULT))

fclean:	clean
	@$(RM) $(NAME)
	@$(RM) $(TEST_NAME)
	@make -C $(LIB_FOLDER) fclean $(NO_PRINT)
	@$(RM) *.gcda
	@$(RM) *.gcno
	@$(RM) vgcore.*
	@($(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE)" FCLEAN "$(DEFAULT))

re: fclean all

debug:	CFLAGS += -g
debug:	clean $(OBJ)
	@make debug -C $(LIB_FOLDER) $(NO_PRINT)
	@$(CC) -Og $(OBJ) -o $(NAME) $(LDFLAGS) $(CSFML_F)

share:
	@make -C $(LIB_FOLDER) $(NO_PRINT)
	@$(CC) -Os -shared -o $(SHARE_NAME) -fPIC $(SRC) $(LDFLAGS) $(CSFML_F) \
	&& $(ECHO) $(BOLD) $(GREEN)"\n► BUILD SHARE SUCCESS !"$(DEFAULT) \
	|| ($(ECHO) $(BOLD) $(RED)"\n► BUILD SHARE FAILED"$(DEFAULT) && exit 1)

test: fclean builder $(TEST_OBJ)
	@make -C $(LIB_FOLDER) $(NO_PRINT)
	@$(CC) $(FLAGS) -o $(TEST_NAME) $(TEST_OBJ) $(TEST_FLAGS) $(LDFLAGS) $(CSFML_F) \
	&& $(ECHO) $(BOLD) $(GREEN)"\n► BUILD TEST SUCCESS !"$(DEFAULT) \
	|| ($(ECHO) $(BOLD) $(RED)"\n► BUILD TEST FAILED"$(DEFAULT) && exit 1)

%.o: %.c
	@$(eval NB=$(shell echo $$(($(NB)+1))))
	@$(CC) -c -o $@ $^ $(CFLAGS) \
	&& python3 build/build.py $< $(NB) $(SRC_COUNT)

.PHONY: all re clean fclean debug test %.o
.SILENT: all re clean fclean debug test %.o
