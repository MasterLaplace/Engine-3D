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
			$(SRC_DIR)draw.c			\
			$(SRC_DIR)wave.c 			\
			$(SRC_DIR)bvh.c				\

TEST	=	$(TEST_DIR)test.c

MAIN		=	$(SRC_DIR)core.c

OBJ			=	$(SRC:.c=.o) $(MAIN:.c=.o)

TEST_OBJ	=	$(SRC:.c=.o) $(TEST:.c=.o)

INCLUDES 	=	-I ./includes -I ./libs/my/include -I ./libs/link/include

LIB_NAME	=	-L ./libs -lmy -llink

OPTI		=	-Ofast -march=native -flto -fuse-linker-plugin -pipe \
				-fomit-frame-pointer -fopenmp -fprefetch-loop-arrays \
				-fno-stack-protector -fno-ident -fno-asynchronous-unwind-tables

IGNORE 		= 	-fno-strict-aliasing -Wno-strict-aliasing

CSFML		=	-l csfml-graphics \
				-l csfml-system \
				-l csfml-window \
				-l csfml-audio

LDFLAGS		=	$(INCLUDES) $(LIB_NAME) $(CSFML) -lm

CFLAGS		=	$(FLAGS) $(LDFLAGS) $(OPTI) $(IGNORE)

ifeq ($(OS), linux)
CC 			:= gcc
NAME 		:=	$(BIN)engine.out
SHARE_NAME	:= 	$(BIN)libengine.so
TEST_NAME 	:=	$(BIN)test_engine.out
else
CC 			:= x86_64-w64-mingw32-gcc
NAME 		:=	$(BIN)engine.exe
SHARE_NAME	:= 	$(BIN)libengine.lib
TEST_NAME 	:=	$(BIN)test_engine.exe
endif

SRC_COUNT 	:= 	$(words $(SRC))
NB 	= 0

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(CFLAGS) \
	&& $(ECHO) $(BOLD) $(GREEN)"\n► BUILD SUCCESS ⛽ !"$(DEFAULT) \
	|| ($(ECHO) $(BOLD) $(RED)"\n► BUILD FAILED ⛽"$(DEFAULT) && exit 1)

all: lib $(NAME)

lib:
	@$(MAKE) all -C ./libs $(NO_PRINT)
	@-$(ECHO) $(BOLD) $(GREEN)"\n► LIB ⛽ !"$(DEFAULT)

## CLEAN TARGETS

clean:
	@$(RM) $(OBJ)
	@$(RM) $(TEST_OBJ)
	@$(MAKE) -C ./libs clean $(NO_PRINT)
	@$(RM) *~
	@$(RM) *#
	@-$(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE)" CLEAN 💨"$(DEFAULT)

fclean:	clean
	@$(RM) $(NAME)
	@$(RM) $(SHARE_NAME)
	@$(RM) $(TEST_NAME)
	@$(MAKE) -C ./libs fclean $(NO_PRINT)
	@$(MAKE) -C ./src/server fclean $(NO_PRINT)
	@$(MAKE) -C ./src/client fclean $(NO_PRINT)
	@$(MAKE) -C ./src/manager fclean $(NO_PRINT)
	@$(RM) *.gcda
	@$(RM) *.gcno
	@$(RM) vgcore.*
	@-$(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE)" FCLEAN 🧻"$(DEFAULT)

re: fclean all

## DEBUG MODE

debug:	OPTI 	= -Og -pipe
debug:	CFLAGS 	= $(OPTI) -g3 -ggdb
debug:	fclean lib_debug $(NAME)
	@-$(ECHO) $(BOLD) $(GREEN)"\n► DEBUG MODE 🔧 !"$(DEFAULT)

lib_debug:
	@$(MAKE) debug -C ./libs $(NO_PRINT)
	@-$(ECHO) $(BOLD) $(GREEN)"\n► LIB DEBUG 🔧 !"$(DEFAULT)

## ANAYLIZE MODE

gprof:	OPTI 	= -Og -pipe
gprof:	CFLAGS 	= $(OPTI) -g3 -ggdb -pg
gprof:	fclean lib_gprof $(NAME)
	@-$(ECHO) $(BOLD) $(GREEN)"\n► GPROF MODE 🤖 !"$(DEFAULT)

lib_gprof:
	@$(MAKE) gprof -C ./libs $(NO_PRINT)
	@-$(ECHO) $(BOLD) $(GREEN)"\n► LIB GPROF 🤖 !"$(DEFAULT)

## INSTALL MODE

share: lib $(OBJ)
	@$(CC) -Os -shared $(CFLAGS) -o $(SHARE_NAME) -fPIC $(SRC) \
	&& $(ECHO) $(BOLD) $(GREEN)"\n► BUILD SHARE SUCCESS 🧲 !"$(DEFAULT) \
	|| ($(ECHO) $(BOLD) $(RED)"\n► BUILD SHARE FAILED 🧲"$(DEFAULT) && exit 1)

install: share
	@-read -r -p "Do you want to install the shared engine library ? [Y/n] " response; \
	if [ $$response = "Y" ] || [ $$response = "y" ] || [ $$response = "" ]; then \
		sudo cp $(SHARE_NAME) /usr/local/lib/ && && sudo ldconfig \
		&& $(ECHO) $(BOLD) $(GREEN)"\n► INSTALL SHARE SUCCESS 🧭!"$(DEFAULT) \
		|| ($(ECHO) $(BOLD) $(RED)"\n► INSTALL SHARE FAILED 🧭"$(DEFAULT) && exit 1) \
	fi

uninstall:
	@-read -r -p "Do you want to uninstall the shared engine library ? [Y/n] " response; \
	if [ $$response = "Y" ] || [ $$response = "y" ] || [ $$response = "" ]; then \
		sudo rm -f /usr/local/lib/libengine.so && sudo ldconfig \
		&& $(ECHO) $(BOLD) $(GREEN)"\n► UNINSTALL SHARE SUCCESS 🧭!"$(DEFAULT) \
		|| ($(ECHO) $(BOLD) $(RED)"\n► UNINSTALL SHARE FAILED 🧭"$(DEFAULT) && exit 1) \
	fi

## TEST MODE

build_tests: CFLAGS += -Wno-deprecated-declarations
build_tests: CFLAGS += -I ./test/include
build_tests: fclean lib_tests $(TEST_OBJ)
	@$(CC) $(CFLAGS) -o $(TEST_NAME) $(TEST_OBJ) \
	&& $(ECHO) $(BOLD) $(GREEN)"\n► BUILD TESTS SUCCESS 🧪 !"$(DEFAULT) \
	|| ($(ECHO) $(BOLD) $(RED)"\n► BUILD TESTS FAILED 🧪"$(DEFAULT) && exit 1)

tests_run: CFLAGS += -Wno-deprecated-declarations
tests_run: CFLAGS += -I ./test/include
tests_run: fclean lib_tests $(TEST_OBJ)
	@$(CC) $(CFLAGS) -o $(TEST_NAME) $(TEST_OBJ) \
	&& $(ECHO) $(BOLD) $(GREEN)"\n► BUILD TESTS SUCCESS 🧪 !"$(DEFAULT) \
	|| ($(ECHO) $(BOLD) $(RED)"\n► BUILD TESTS FAILED 🧪"$(DEFAULT) && exit 1)
	./$(TEST_NAME) -e

lib_tests:
	@$(MAKE) tests_run -C ./libs $(NO_PRINT)
	@$(ECHO) $(BOLD) $(GREEN)"\n► LIB TESTS 🧪 !"$(DEFAULT)

%.o: %.c
	@$(eval NB=$(shell echo $$(($(NB)+1))))
	@-$(CC) -c -o $@ $^ $(CFLAGS) \
	&& python3 build/build.py $< $(NB) $(SRC_COUNT)

server:
	@$(MAKE) all -C ./src/server $(NO_PRINT)

client:
	@$(MAKE) all -C ./src/client $(NO_PRINT)

manager:
	@$(MAKE) all -C ./src/manager $(NO_PRINT)

author:
	@echo $(USER)

version:
	@echo $(VERSION)

.PHONY: all re clean fclean debug test %.o
.SILENT: all re clean fclean debug test %.o
