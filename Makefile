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

PROJECT_NAME	:=	$(word 2, $(MAKECMDGOALS))
GRAPHICAL_LIB	:=	$(word 3, $(MAKECMDGOALS))

DEFAULT_GRAPHICAL_LIB := csfml

SRC_DIR		=	./Engine/

# SRC			=	$(shell find $(SRC_DIR) -name '*.c' | grep -v "core.c")
MAIN		=	$(SRC_DIR)core.c

MAIN_OBJ	=	$(MAIN_SRC:.c=.o)

BIN 		=	bin/

INCLUDES	=	-I ./Libs/LaplaceLib/include -I ./Libs/LaplaceLink/include \
				-I ./Libs/LaplaceMap/include -I ./Libs/LaplaceError/include \
				-I ./Engine/Engine

LIB_NAME	=	-L ./Libs -l LaplaceLib -l LaplaceLink -l LaplaceMap

OPTI		=	-Ofast -march=native -flto -fuse-linker-plugin -pipe \
				-fomit-frame-pointer -fopenmp -fprefetch-loop-arrays \
				-fno-stack-protector -fno-ident -fno-asynchronous-unwind-tables

IGNORE		= 	-fno-strict-aliasing -Wno-strict-aliasing

CSFML		=	-l csfml-graphics \
				-l csfml-system   \
				-l csfml-window   \
				-l csfml-audio

SFML		=	-l sfml-graphics \
				-l sfml-system   \
				-l sfml-window   \
				-l sfml-audio

SDL2		=	-l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

OPENGL		=	-l glfw -l GLEW -l GL -l GLU -l glut -l X11 -l dl -l pthread -l Xrandr \
				-l Xi -l Xxf86vm -l Xinerama -l Xcursor

VULKAN		=	-l glfw -l vulkan -l X11 -l dl -l pthread -l Xrandr \
				-l Xi -l Xxf86vm -l Xinerama -l Xcursor

LDFLAGS :=
ifeq ($(GRAPHICAL_LIB), csfml)
    LDFLAGS := $(INCLUDES) $(LIB_NAME) $(CSFML) -lm
else ifeq ($(GRAPHICAL_LIB), sfml)
    LDFLAGS := $(INCLUDES) $(LIB_NAME) $(SFML) -lm
else ifeq ($(GRAPHICAL_LIB), sdl2)
    LDFLAGS := $(INCLUDES) $(LIB_NAME) $(SDL2) -lm
else ifeq ($(GRAPHICAL_LIB), opengl)
    LDFLAGS := $(INCLUDES) $(LIB_NAME) $(OPENGL) -lm
else ifeq ($(GRAPHICAL_LIB), vulkan)
    LDFLAGS := $(INCLUDES) $(LIB_NAME) $(VULKAN) -lm
else
    # If no graphical lib is specified, use the default one
    LDFLAGS := $(INCLUDES) $(LIB_NAME) $(CSFML) -lm
    GRAPHICAL_LIB := $(DEFAULT_GRAPHICAL_LIB)
endif

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

$(PROJECT_NAME):
	@$(ECHO) $(BOLD) $(LIGHT_BLUE) "Selected project: $(PROJECT_NAME) 🎮 !" $(DEFAULT)

$(GRAPHICAL_LIB):
	@$(ECHO) $(BOLD) $(LIGHT_BLUE) "Selected graphical library: $(GRAPHICAL_LIB) 🎮 !" $(DEFAULT)

$(NAME): print lib $(MAIN_OBJ)
	@$(CC) -o $(NAME) ok.c \
	&& $(ECHO) $(BOLD) $(GREEN)"\n► BUILD SUCCESS ⛽ !"$(DEFAULT) \
	|| ($(ECHO) $(BOLD) $(RED)"\n► BUILD FAILED ⛽"$(DEFAULT) && exit 1)


all: $(NAME) $(PROJECT_NAME) $(GRAPHICAL_LIB)

print:
	@$(ECHO) $(BOLD)$(GREEN)"🚀  Engine-3D  🚀"$(DEFAULT)
	@$(ECHO) $(BOLD) $(GREEN)"\n► MAKEFILE 📖 !"$(DEFAULT)

lib:
	@$(MAKE) all -C ./Libs $(NO_PRINT)
	@-$(ECHO) $(BOLD) $(GREEN)"\n► LIB ⛽ !"$(DEFAULT)

launcher:
	@ln -sf ./Launcher/src/main.py ./launcher
	@-$(ECHO) $(BOLD) $(GREEN)"\n► LAUNCHER 🚀 !"$(DEFAULT)
	@$(MAKE) all -C ./Launcher $(NO_PRINT)

run: all
	@-./bin/engine.out $(PROJECT_NAME) \
	&& $(ECHO) $(BOLD) $(GREEN)"\n► RUN SUCCESS 🚀 !"$(DEFAULT) \
	|| ($(ECHO) $(BOLD) $(RED)"\n► RUN FAILED 🚀"$(DEFAULT) && exit 1)

## CLEAN TARGETS

clean:
	@$(RM) $(OBJ)
	@$(RM) $(TEST_OBJ)
	@$(MAKE) -C ./Libs clean $(NO_PRINT)
	@$(MAKE) -C ./Launcher clean $(NO_PRINT)
	@$(RM) *~
	@$(RM) *#
	@-$(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE)" CLEAN 💨"$(DEFAULT)

fclean:	clean
	@$(RM) $(NAME)
	@$(RM) $(SHARE_NAME)
	@$(RM) $(TEST_NAME)
	@$(MAKE) -C ./Libs fclean $(NO_PRINT)
	@$(MAKE) -C ./Launcher fclean $(NO_PRINT)
	@$(RM) *.gcda
	@$(RM) *.gcno
	@$(RM) vgcore.*
	@-$(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE)" FCLEAN 🧻"$(DEFAULT)

re: fclean all launcher

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
