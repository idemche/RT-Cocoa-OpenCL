/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 17:46:29 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/07 16:58:20 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_LIBFT_H
# define LIBFT_LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <OpenCL/OpenCL.h>
# include <math.h>

# define VEC3 cl_float3

typedef struct	s_list
{
	void				*content;
	size_t				content_size;
	struct s_list		*next;
}				t_list;

void			*ft_realloc(void *data, size_t old_size, size_t new_size);
void			*ft_memset(void *dst, int c, size_t n);
void			ft_bzero(void *dst, size_t n);
void			*ft_memcpy(void *s1, const void *s2, size_t n);
void			*ft_memccpy(void *dest, const void *src, int c, size_t n);
void			*ft_memmove(void *s1, const void *s2, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
size_t			ft_strlen(const char *src);
char			*ft_strdup(const char *src);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t n);
char			*ft_strcat(char *dest, const char *src);
char			*ft_strncat(char *dest, const char *src, size_t n);
size_t			ft_strlcat(char *dst, const char *src, size_t siz);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *s1, const char *s2);
char			*ft_strnstr(const char *s1, const char *s2, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *str);
int				ft_isalpha(int c);
int				ft_isnum(char *s);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_islower(int c);
int				ft_isupper(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_isspace(char c);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char(*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, size_t start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char c);
char			*ft_itoa(int n);
void			ft_putchar(char c);
void			ft_putstr(char const *s);
void			ft_putendl(char const *s);
void			ft_putnbr(int n);
char			*ft_strrev(char *str);
int				ft_power(int nb, int pow);
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
void			ft_swap(int *a, int *b);
char			*ft_strupcase(char *str);
char			*ft_strlowcase(char *str);
int				ft_strisupper(char *str);
int				ft_strislower(char *str);
int				ft_strisalpha(char *str);
int				ft_strisdigit(char *str);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstaddend(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int				ft_countwords(char *str, char c);
char			*ft_getword(const char *s, char c, int *i);
int				ft_sizeofnumber(int n);
int				ft_atoi_base(const char *nptr, const char *base);
int				*ft_strsplittoint(char const *s, char c);
char			*ft_merge(char *a, char *b);
cl_float		dot_3(VEC3 v1, VEC3 v2);
void			normalise_vec3(VEC3 *v);
VEC3			i_3(cl_float x, cl_float y, cl_float z);
VEC3			sub_vec3(VEC3 v1, VEC3 v2);
VEC3			mult_3(VEC3 vector, cl_float c);
VEC3			add_vec3(VEC3 v1, VEC3 v2);
VEC3			cross_prod(VEC3 v1, VEC3 v2);

#endif
