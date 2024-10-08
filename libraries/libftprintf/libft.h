/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/17 16:42:35 by rmaes         #+#    #+#                 */
/*   Updated: 2024/08/08 19:37:07 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

int				ft_abs(int n);
int				ft_atoi(const char *str);
unsigned long	ft_atoul(const char *str);
void			*ft_bzero(void *e, size_t len);
size_t			ft_strlen(const char *s);
void			*ft_calloc(size_t count, size_t size);
int				ft_fprintf(int fd, const char *content, ...);
int				ft_is_atoi(char *s);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
char			*ft_itoa(int n);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
t_list			*ft_lstnew(void *content);
int				ft_lstsize(t_list *lst);
void			*ft_memchr(const void *c, int s, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *d, const void *s, size_t len);
void			*ft_memset(void *e, int c, size_t len);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);
int				ft_count_word(char const *s, char c);
char			**ft_split(char const *s, char c);
char			*ft_strchr(const char *s, int c);
char			*ft_strdup(const char *s1);
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlen(const char *s);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *haystack,
					const char *ndl, size_t len);
char			*ft_strrchr(const char *s, int c);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);
int				ft_tolower(int c);
int				ft_toupper(int c);
int				ft_min(int n, int d);
int				ft_max(int n, int d);
int				ft_btw(int n, int d, int i);
char			*ft_ultoa(unsigned long n);
int				ft_printf(const char *content, ...);
int				ft_strcmp(const char *str1, const char *str2);
char			*get_next_line(int fd);
void			*ft_realloc(void *ptr, size_t size);
int				ft_digitcount(long int n);
int				ft_digitcount_unsigned(unsigned long n);
int				ft_is_negative(unsigned long n);
int				ft_sign(int n);
char			*ft_tristrjoin(char const *s1, char const *s2, char const *s3);

#endif