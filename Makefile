# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jimpark <jimpark@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/31 02:10:37 by hwankim           #+#    #+#              #
#    Updated: 2023/04/09 12:46:58 by jimpark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

CC				= cc
RM				= rm -rf
CFLAGS			= -Wall -Wextra -Werror -g -fsanitize=address

# READLINE_LIB 	= -lreadline -L/opt/homebrew/opt/readline/lib
# READLINE_INC	= -I/opt/homebrew/opt/readline/include

READLINE_LIB = -lreadline -L/Users/jimpark/.brew/opt/readline/lib
READLINE_INC = -I/Users/jimpark/.brew/opt/readline/include

LIB_DIR			= ./libft
HEADER			= ./includes
INCLUDES		= -I$(HEADER) -I$(LIB_DIR)

SRC1			= ./srcs/main.c

SRC2			= ./srcs/tree/tree.c \
				  ./srcs/tree/tree_delete.c \
				  ./srcs/signal/signal.c \
				  ./srcs/signal/signal2.c

SRC3			= ./srcs/tokenizer/tokenizer.c \
				  ./srcs/tokenizer/utils.c \
				  ./srcs/tokenizer/get_env.c \
				  ./srcs/tokenizer/get_env2.c \
				  ./srcs/tokenizer/get_env3.c \
				  ./srcs/tokenizer/utils2.c \
				  ./srcs/tokenizer/utils3.c

SRC4			= ./srcs/parsing/parsing.c \
				  ./srcs/parsing/parsing2.c \
				  ./srcs/parsing/parsing_check_type.c \
				  ./srcs/parsing/parsing_add_scmd.c \
				  ./srcs/parsing/parsing_heredoc.c

SRC5			= ./srcs/execution/execution.c \
				  ./srcs/execution/execute_cmd.c \
				  ./srcs/execution/redirection.c \
				  ./srcs/execution/error.c \
				  ./srcs/execution/execute_builtin.c \
				  ./srcs/execution/execution2.c \
				  ./srcs/execution/set_redirection_open.c \
				  ./srcs/execution/execution_utils.c

SRC6			= ./srcs/builtin/builtin_perform_pwd.c \
				  ./srcs/builtin/builtin_perform_echo.c \
				  ./srcs/builtin/builtin_utils.c \
				  ./srcs/builtin/builtin_perform_env.c \
				  ./srcs/builtin/builtin_perform_cd.c \
				  ./srcs/builtin/builtin_perform_export.c \
				  ./srcs/builtin/builtin_perform_export2.c \
				  ./srcs/builtin/builtin_utils2.c \
				  ./srcs/builtin/builtin_utils3.c \
				  ./srcs/builtin/builtin_perform_unset.c \
				  ./srcs/builtin/builtin_perform_exit.c

SRCS			= $(SRC1) $(SRC2) $(SRC3) $(SRC4) $(SRC5) $(SRC6)

OBJS			= $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(READLINE_INC) -o $@ -c $<

$(NAME):		$(OBJS)
				make bonus -C $(LIB_DIR)
				$(CC) $(CFLAGS) $(INCLUDES) $(READLINE_LIB) $(READLINE_INC) -L $(LIB_DIR) -lft -o $(NAME) $(OBJS)

all:			$(NAME)

clean:
				make -C $(LIB_DIR) clean
				$(RM) $(OBJS)

fclean:			clean
				make -C $(LIB_DIR) fclean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			clean fclean all re
