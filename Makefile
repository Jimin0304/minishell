NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

HEADER = -I ./include
SRC_DIR = ./src/

READLINE_LIB = -lreadline -L /Users/jimpark/.brew/opt/readline/lib
READLINE_INC = -I /Users/jimpark/.brew/opt/readline/include

SRCS = 	$(SRC_DIR)minishell.c \
		$(SRC_DIR)parse.c \
		$(SRC_DIR)utils.c \
		$(SRC_DIR)check.c

OBJECTS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJECTS)
			$(CC) $(CFLAGS) $(HEADER) $(READLINE_LIB) $(OBJECTS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(READLINE_INC) -c $< -o $@

clean :
	$(RM) $(OBJECTS)

fclean : clean
	$(RM) $(NAME)
re :
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re bonus
