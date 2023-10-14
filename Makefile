##
## EPITECH PROJECT, 2023
## Title: Engine-3D
## Author: MasterLaplace
## Created: 2023-10-13
## File description:
## Makefile
##

-include .env
export

BIN 		=	bin/

INCLUDES	=	-I ./includes -I ./libs/my/include -I ./libs/link/include

LIB_NAME	=	-L ./libs -lmy -llink

OPTI		=	-Ofast -march=native -flto -fuse-linker-plugin -pipe \
				-fomit-frame-pointer -fopenmp -fprefetch-loop-arrays \
				-fno-stack-protector -fno-ident -fno-asynchronous-unwind-tables

IGNORE		= 	-fno-strict-aliasing -Wno-strict-aliasing

CSFML		=	-l csfml-graphics \
				-l csfml-system   \
				-l csfml-window   \
				-l csfml-audio


LDFLAGS		=	$(INCLUDES) $(LIB_NAME) $(CSFML) -lm

CFLAGS		=	$(FLAGS) $(LDFLAGS) $(OPTI) $(IGNORE)

ifeq ($(OS), linux)
CC			:=	gcc
NAME		:=	$(BIN)engine.out
SHARE_NAME	:=	$(BIN)libengine.so
TEST_NAME 	:=	$(BIN)test_engine.out
endif
ifeq ($(OS), windows)
CC			:=	gcc
NAME		:=	$(BIN)engine.exe
SHARE_NAME	:=	$(BIN)libengine.dll
TEST_NAME	:=	$(BIN)test_engine.exe
endif
ifeq ($(OS), macos)
CC			:=	clang
NAME		:=	$(BIN)engine.out
SHARE_NAME	:=	$(BIN)libengine.dylib
TEST_NAME	:=	$(BIN)test_engine.out
endif
ifeq ($(OS), bsd)
CC			:=	clang
NAME		:=	$(BIN)engine.out
SHARE_NAME	:=	$(BIN)libengine.dylib
TEST_NAME	:=	$(BIN)test_engine.out
endif

SRC_COUNT	:=	$(words $(SRC))
NB	= 0

all: lib $(NAME)

lib:
	@$(MAKE) all -C ./Libs $(NO_PRINT)
	@-$(ECHO) $(BOLD) $(GREEN)"\n► LIB ⛽ !"$(DEFAULT)

## CLEAN TARGETS

clean:
	@$(RM) $(OBJ)
	@$(RM) $(TEST_OBJ)
	@$(MAKE) -C ./Libs clean $(NO_PRINT)
	@$(RM) *~
	@$(RM) *#
	@-$(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE)" CLEAN 💨"$(DEFAULT)

fclean:	clean
	@$(RM) $(NAME)
	@$(RM) $(SHARE_NAME)
	@$(RM) $(TEST_NAME)
	@$(MAKE) -C ./Libs fclean $(NO_PRINT)
	@$(RM) *.gcda
	@$(RM) *.gcno
	@$(RM) vgcore.*
	@-$(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE)" FCLEAN 🧻"$(DEFAULT)

re: fclean all

## DEBUG MODE

debug: OPTI		= -Og -pipe
debug: CFLAGS	= $(FLAGS) $(LDFLAGS) $(OPTI) $(IGNORE) -g3 -ggdb -DDEBUG
debug: fclean lib_debug $(NAME)
	@-$(ECHO) $(BOLD) $(GREEN)"\n► DEBUG MODE 🔧 !"$(DEFAULT)

lib_debug:
	@$(MAKE) debug -C ./Libs $(NO_PRINT)
	@-$(ECHO) $(BOLD) $(GREEN)"\n► LIB DEBUG 🔧 !"$(DEFAULT)

## ANAYLIZE MODE

gprof: OPTI		+= -fno-omit-frame-pointer
gprof: CFLAGS	= $(FLAGS) $(LDFLAGS) $(OPTI) $(IGNORE) -pg
gprof: fclean lib_gprof $(NAME)
	@-$(ECHO) $(BOLD) $(GREEN)"\n► GPROF MODE 🤖 !"$(DEFAULT)

lib_gprof:
	@$(MAKE) gprof -C ./Libs $(NO_PRINT)
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

lib_tests:
	@$(MAKE) tests_run -C ./libs $(NO_PRINT)
	@$(ECHO) $(BOLD) $(GREEN)"\n► LIB TESTS 🧪 !"$(DEFAULT)

%.o: %.c
	@$(eval NB=$(shell echo $$(($(NB)+1))))
	@-$(CC) -c -o $@ $^ $(CFLAGS) \
	&& python3 Scripts/improve_build.py $< $(NB) $(SRC_COUNT)

## HELP MODE

help:
	@$(ECHO) $(BOLD) $(GREEN)"\n► HELP MODE 📖 !"$(DEFAULT)
	@$(ECHO) $(BOLD) $(GREEN)"\n► MAKEFILE COMMANDS 📖 !"$(DEFAULT)
	@$(ECHO) $(BOLD) $(LIGHT_BLUE)"\n► make\
	\n► make re\
	\n► make clean\
	\n► make fclean\
	\n► make debug\
	\n► make gprof\
	\n► make share\
	\n► make install\
	\n► make uninstall\
	\n► make help\
	\n► make author\
	\n► make version"$(DEFAULT)
	@$(ECHO) $(BOLD) $(GREEN)"\n► LIB COMMANDS 📖 !"$(DEFAULT)
	@$(ECHO) $(BOLD) $(LIGHT_BLUE)"\n► make lib\
	\n► make lib_debug\
	\n► make lib_gprof\
	\n► make lib_tests"$(DEFAULT)
	@$(ECHO) $(BOLD) $(GREEN)"\n► GRAPHICAL LIBRARIES 📖 !"$(DEFAULT)
	@$(ECHO) $(BOLD) $(LIGHT_BLUE)"\n► make csfml\
	\n► make sfml\
	\n► make sdl2\
	\n► make opengl\
	\n► make vulkan"$(DEFAULT)

author:
	@$(ECHO) $(USER)

version:
	@$(ECHO) $(BOLD) $(GREEN)"\n► VERSION 📖 !"$(DEFAULT)
	@$(ECHO) $(BOLD) $(LIGHT_BLUE)"\n► $(VERSION) 📖 !"$(DEFAULT)
	@$(MAKE) -C ./Libs version $(NO_PRINT)


.PHONY: all re clean fclean debug test %.o
.SILENT: all re clean fclean debug test %.o
