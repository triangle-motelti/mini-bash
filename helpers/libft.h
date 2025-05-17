/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:37:03 by aamraouy          #+#    #+#             */
/*   Updated: 2025/05/16 09:33:23 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "../minishell.h"


void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void exit_error(const char *msg);
t_token	*ft_lstnew(void *content, int type);
t_token	*ft_lstlast(t_token *lst);
void	ft_lstadd_back(t_token **lst, t_token *new);

int ft_strrchr_advance(char *s, char *str_to_find);

char	quotes_syntax(char *input);
int	ft_lstsize(t_token *lst);
void	clear_tokens(t_token **tokens);

size_t	ft_strlen(const char *str);
int		ft_isdigit(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
char	*ft_itoa(int n);
int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		ft_isascii(int c);
int		ft_isprint(int c);
void	*ft_memset(void *str, int c, size_t size);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strrchr(const char *s, int c);
// int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

char	*ft_strndup(char *s, size_t n);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strcat(char *dest, char *src);
int		ft_strcmp(const char *a, const char *b);
char	*ft_strjoin_sep(const char *s1, const char *s2, const char *sep);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		ft_isnumber(const char *str);

#endif