/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 12:00:43 by siferrar          #+#    #+#             */
/*   Updated: 2020/08/24 12:55:15 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <strings.h>
# include "../srcs/Files/GNL/get_next_line.h"
# include "../srcs/Printf/includes/printf.h"

# define PI 3.14159265358979323846264338327950288

long				ft_abs(long n);
int					ft_atoi(const char *str);
void				*ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t count, size_t size);
char				*ft_itoa(int n);
char				*ft_ftoa(float n, int dec);
int					*ft_str_to_int_tab(const char *s1);
int					ft_findchar(const char *needles, const char *str);
double				ft_indeg(double angle);
double				ft_inrad(double angle);
float				ft_to_360(float angle);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
char				*ft_itoab(long value, int base);
void				*ft_memccpy(void *d, const void *s, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
int					ft_putchar(int c);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putunbr(unsigned int n);
size_t				ft_putnbr(long n);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putstr(char *str);
size_t				ft_putnstr(char *str, size_t maxlen);
size_t				ft_putihex(unsigned int n, int upper);
size_t				ft_puthex(unsigned long n, int upper);
void				ft_putint(char *name, int nbr);
char				**ft_split(char const *s, char c);
void				ft_free_split(char **splited);
char				*ft_check_str(char *str, char *chrs);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(const char *s1);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *s);
size_t				ft_hexlen(unsigned int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *haystack, const char *needle,
								size_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strupper(const char *str);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_ilen(int n);
size_t				ft_ulen(unsigned int n);
size_t				ft_llen(long n);
typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **alst, t_list *newlst);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **alst, t_list *newlst);
void				ft_lstiter(t_list *lst, void (*f)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstclear(t_list **lst, void (*del)(void*));
t_list				*ft_lstmap(t_list *lst,
								void *(*f)(void *),
								void (*del)(void *));
int					get_next_line(int fd, char **line, int meditate_gnl);
#endif
