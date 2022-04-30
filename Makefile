# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/07 16:28:21 by gvarys            #+#    #+#              #
#    Updated: 2022/03/05 16:04:00 by ereginia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	minishell

CC					=	gcc
CFLAGS				=	-g3 -O2 -Wall -Wextra -Werror

HOME_FLAGS			=	-L${HOME}/.brew/opt/readline/lib -I${HOME}/.brew/opt/readline/include

RM					=	rm -rf

SRC_DIR				=	src/

HEADER_DIR			=	includes/

LIBFT_DIR			=	libft/
LIBFT				=	$(LIBFT_DIR)/libft.a

HEADER				=	$(HEADER_DIR)minishell.h

SRC_FILES			=	main.c\
						utils/minishell_utils.c\
						utils/pipes_and_pids.c\
						utils/execute_and_redirects.c\
						utils/error.c\
						utils/clean.c\
						builtins/utils.c\
						builtins/unset.c\
						builtins/env.c\
						builtins/exit.c\
						builtins/pwd.c\
						builtins/export.c\
						builtins/cd.c\
						builtins/echo.c\
						envs/envs.c\
						envs/envs_utils.c\
						executable/exe.c\
						executable/exe_utils.c\
						signals/signals.c\
						parser/parser.c\
						parser/parser_utils.c\
						parser/ft_split_delux.c\
						parser/inseption_split.c\
						parser/inseption_split_utils.c\
						parser/comma_killer.c\
						parser/some_stuff.c

OBJS				=	$(patsubst %.c, %.o, $(addprefix $(SRC_DIR), $(SRC_FILES)))

all					:	$(LIBFT) $(NAME)

$(LIBFT)			:
							make -C $(LIBFT_DIR)

$(NAME)				:	$(OBJS)
							$(CC) $(CFLAGS)  -lreadline $(HOME_FLAGS) -L$(LIBFT_DIR) -lft $(OBJS) -o $@

%.o					:	%.c $(HEADER)
							$(CC) $(CFLAGS) -I$(HEADER_DIR) -c $< -o $@

clean				:
							$(RM) $(OBJS)
							make -C $(LIBFT_DIR) clean

fclean				:	clean
							$(RM) $(NAME)
							make -C $(LIBFT_DIR) fclean

re					:	fclean all

.PHONY				:	all clean fclean re
