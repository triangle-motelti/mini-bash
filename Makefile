# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: motelti <motelti@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/17 20:38:41 by motelti           #+#    #+#              #
#    Updated: 2025/04/29 14:07:47 by motelti          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc
# CFLAGS	= -Wall -Werror -Wextra
RM		= @rm -f


NAME	= minishell
HEADER = minishell.h

LIBFT_SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_isnumber.c \
	ft_memchr.c ft_memcmp.c ft_memcpy.c ft_strtok.c ft_strcmp.c \
	ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_strjoin_sep.c \
	ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strndup.c \
	ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
	ft_strlen.c ft_strmapi.c ft_striteri.c ft_strncmp.c \
	ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \


PARSER_SRC = parsing.c parse_utils.c 

ENVP_SRC = envp_build.c

EXEC_SRC = path.c exec.c exec_builtins.c exec_cmd.c

PIPE_SRC = pipe.c pipe_utils.c helpers.c

BUILTINS_SRC = cd.c echo.c exit.c pwd.c export.c env.c builtin.c  export_utils.c \
			unset.c

MAINSHELL_SRC = main.c

SRC		= $(addprefix ./helpers/, $(LIBFT_SRC)) \
		$(addprefix ./parser/, $(PARSER_SRC)) \
		$(addprefix ./envp/, $(ENVP_SRC)) \
		$(addprefix ./pipe/, $(PIPE_SRC)) \
		$(addprefix ./excution/, $(EXEC_SRC)) \
		$(addprefix ./builtins/, $(BUILTINS_SRC)) \
		$(addprefix ./mainshell/, $(MAINSHELL_SRC))

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
