##
## EPITECH PROJECT, 2023
## Engine-3D
## File description:
## Makefile
##

-include .env
export

SRC_DIR 	= 	src/engine/

TEST_DIR 	= 	test/engine/

BIN 		=	bin/

SRC		=   $(SRC_DIR)init.c			\
			$(SRC_DIR)init_textures.c	\
			$(SRC_DIR)preset_textures.c	\
			$(SRC_DIR)clean.c			\
			$(SRC_DIR)parser_obj.c 		\
			$(SRC_DIR)help.c			\
			$(SRC_DIR)loop.c 			\
			$(SRC_DIR)event.c			\
			$(SRC_DIR)rasterization.c	\
			$(SRC_DIR)clipping.c		\
			$(SRC_DIR)utils.c			\
			$(SRC_DIR)merge_sort.c		\
			$(SRC_DIR)draw.c			\
			$(SRC_DIR)wave.c 			\
			$(SRC_DIR)bvh.c	\

TEST	=	$(TEST_DIR)test.c

builder:
ifeq ($(OS), linux)
CC := gcc
NAME :=	$(BIN)engine.out
else
CC := x86_64-w64-mingw32-gcc
NAME :=	$(BIN)engine.exe
endif

MAIN		=	$(SRC_DIR)core.c

OBJ			=	$(SRC:.c=.o) $(MAIN:.c=.o)

TEST_OBJ	=	$(SRC:.c=.o) $(TEST:.c=.o)

SHARE_NAME = 	$(BIN)engine.so

TEST_NAME 	=	$(BIN)test_engine.out

INCLUDE 	=	./includes

LIB_FOLDER	=	./lib

LIB_NAME	=	my

LDFLAGS		=	-L $(LIB_FOLDER) -l $(LIB_NAME) -lm

CFLAGS		=	$(FLAGS) -I $(INCLUDE)

TEST_FLAGS	=	-I ./test/include

CSFML_F		=	-l csfml-graphics -l csfml-system -l csfml-window -l csfml-audio

SRC_COUNT 	:= 	$(words $(SRC))
NB 	= 0

$(NAME): builder $(OBJ)
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
	@make -C ./src/server fclean $(NO_PRINT)
	@make -C ./src/client fclean $(NO_PRINT)
	@$(RM) *.gcda
	@$(RM) *.gcno
	@$(RM) vgcore.*
	@($(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE)" FCLEAN "$(DEFAULT))

re: fclean all

debug:	CFLAGS += -g
debug:	fclean $(OBJ)
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

server:
	@make all -C ./src/server $(NO_PRINT)

client:
	@make all -C ./src/client $(NO_PRINT)

.PHONY: all re clean fclean debug test %.o
.SILENT: all re clean fclean debug test %.o
