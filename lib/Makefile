##
## ME PROJECT, 2022
## B-PSU-210-REN-2-1-minishell2-guillaume.papineau
## File description:
## Makefile
##

-include .env
export

LINK 	= link/

MY		= my/

SRC =	$(LINK)append_link.c 	\
		$(LINK)appstart_link.c 	\
		$(LINK)create_link.c 	\
		$(LINK)is_null_link.c 	\
		$(LINK)len_link.c 		\
		$(LINK)remove_link.c 	\
		$(LINK)swap_link.c 		\
		$(MY)char_in_list.c 	\
		$(MY)count_char.c 		\
		$(MY)openfile.c 		\
		$(MY)strcat.c 			\
		$(MY)stwa.c				\
		$(MY)two_free.c 		\
		$(MY)two_len.c 			\

CFLAGS	=	 -I ../includes

OBJ	=	$(SRC:.c=.o)

NAME	=	libmy.a

SRC_COUNT := $(words $(SRC))
NB = 0

all:	$(NAME)

$(NAME):	$(OBJ)
	@$(ECHO)
	@($(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE) \
	"Lib files sucessfully build. "$(DEFAULT))
	@ar rc $(NAME) $(OBJ)

clean:
	@$(RM) $(OBJ)
	@($(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE)" CLEAN LIBMY "$(DEFAULT))

fclean: clean
	@$(RM) $(NAME)
	@($(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE)" FCLEAN LIBMY "$(DEFAULT))

re: fclean all

debug:	CFLAGS += -g
debug:	re

%.o: %.c
	@$(eval NB=$(shell echo $$(($(NB)+1))))
	@$(CC) -c -o $@ $^ $(CFLAGS) \
	&& python3 ../build/build.py $< $(NB) $(SRC_COUNT)

.PHONY: all re clean fclean debug %.o