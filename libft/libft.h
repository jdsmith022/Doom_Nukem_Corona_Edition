/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/13 12:48:31 by jesmith        #+#    #+#                */
/*   Updated: 2020/02/17 19:21:40 by mminkjan      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <string.h>
# include "get_next_line.h"
// # include "graphics.h"

void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *str, int c, size_t n);
void				*ft_memcpy(void *dst, const void *str, size_t n);
void				*ft_memccpy(void *dst, const void *str, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);

char				*ft_strcpy(char *dst, const char *src);
char				*ft_strdup(const char *s1);
char				*ft_strncpy(char *dst, const char *src, size_t n);
size_t				ft_strlen(const char *str);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strcat(char *src1, const char *src2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnew(size_t size);
void				ft_strarray_del(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack, const char \
					*needle, size_t len);
char				*ft_strndup(const char *s1, size_t n);
char				**ft_strplit(char const *s, char c);
void				ft_strdel(const char *s);
size_t				ft_strclen(const char *s, char c);
char				*ft_stralloc(const char *s);
char				*ft_strrev(char *s);
int					ft_strsubsize(char *str);
void				ft_free_strarray(char **str);

size_t				ft_wrdcount(char const *s, char c);

void				ft_del(void *data, size_t size);
void				ft_exit(char *str, int fd);

int					ft_atoi(const char *str);
int					ft_atoi_base(const char *str, int base);
char				*ft_itoa(int n);
char				*ft_itoa_base(int n, int base);

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isdigit_base(char c, int base);
int					ft_iswhitespace(int c);
void				ft_is_negative(int n);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_isspace(int c);
int					ft_islower(int c);
int					ft_isupper(int c);
int					ft_isnumber_base(char *nb, int base);
int					ft_has_prefix(const char *str, int base);

void				ft_putchar(char c);
void				ft_putendl(char const *s);
void				ft_putstr(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);

int					ft_intlen(int n);
unsigned int		ft_ull_length(unsigned long long num, unsigned int base);
int					ft_count_if(char **tab, int (*f)(char *));
void				ft_foreach(int *tab, int length, void (*f)(int));
int					*ft_range(int min, int max);
int					ft_sqrt(int nb);
int					ft_recursive_factorial(int nb);
void				ft_div_mod(int a, int b, int *div, int *mod);
void				ft_swap(int *a, int *b);
void				ft_print_numbers(void);
void				ft_print_alphabet(void);

int					get_next_line(const int fd, char **line);

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstnew(void const *content, size_t content_size);
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstaddback(t_list **alst, t_list *blst);

#endif
