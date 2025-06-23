# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: motelti <motelti@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/17 20:38:41 by motelti           #+#    #+#              #
#    Updated: 2025/06/23 22:31:01 by motelti          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc
CFLAGS	= -Wall -Werror -Wextra -fsanitize=address
RM		= @rm -f


NAME	= minishell
HEADER = minishell.h

LIBFT_SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_strcat.c ft_strcmp.c \
	ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_memcpy.c  \
	ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strcpy.c \
	ft_strdup.c ft_strjoin.c ft_strlcpy.c ft_isnumber.c \
	ft_strlen.c ft_strncmp.c ft_strndup.c \
	ft_substr.c ft_lstnew.c  quotes.c  ft_strjoin_sep.c \
	ft_lstlast.c ft_lstadd_back.c ft_lstclear.c check_stuff.c ft_lstsize.c \
	ft_realloc.c ft_strrchr.c

EXPENDER_SRC = expander.c utils.c ambiguous.c more_utils.c maximum_utils.c

PARSER_SRC = parser.c  token_utils.c tokenizer.c

ENVP_SRC = envirement.c build_env.c env_utils.c 

SIG_SRC = signal.c

FREE_MEM_SRC = free_memory.c

REDIREC_SRC = redirections.c redir_utils.c herdoc.c heredoc_utils.c helpers.c

BUILD_CMD_SRC =  build_cmd.c cmd_utils.c cmd_helpers.c

EXEC_SRC = exec_single_cmd.c exec_builtins.c path.c exe_sngl_cmd_utlis.c 

PIPE_SRC = pipe.c pipe_utils.c

BUILTINS_SRC = cd.c echo.c exit.c pwd.c export.c env.c builtin.c  export_utils.c \
			unset.c export_helpers.c export_utils2.c

MAINSHELL_SRC = main.c main_utils.c

SRC		= $(addprefix ./helpers/, $(LIBFT_SRC)) \
		$(addprefix ./expander/, $(EXPENDER_SRC)) \
		$(addprefix ./free_mem/, $(FREE_MEM_SRC)) \
		$(addprefix ./exec/, $(EXEC_SRC)) \
		$(addprefix ./envirement/, $(ENVP_SRC)) \
		$(addprefix ./signals/, $(SIG_SRC)) \
		$(addprefix ./redirections/, $(REDIREC_SRC)) \
		$(addprefix ./pipe/, $(PIPE_SRC)) \
		$(addprefix ./builtins/, $(BUILTINS_SRC)) \
		$(addprefix ./parsing_am/, $(PARSER_SRC)) \
		$(addprefix ./command_build/, $(BUILD_CMD_SRC)) \
		$(addprefix ./main/, $(MAINSHELL_SRC))

OBJ		= $(SRC:.c=.o)



all: $(NAME) clean


%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ -MMD


$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lreadline -o $(NAME)

clean:
	$(RM) $(OBJ) $(BONUS_OBJ) $(OBJ:.o=.d)

fclean: clean
	$(RM) $(NAME)

re: fclean all

-include $(OBJ:.o=.d)
