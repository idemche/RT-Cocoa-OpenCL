#ifndef UTIL_H
# define UTIL_H

# include "rt.h"

typedef unsigned char	t_uch;
typedef unsigned int	t_uint;
typedef struct s_info	t_info;
typedef struct	s_cl	t_cl;

void			ft_error(char *str);
void			ft_warning(char *str);
void			ft_error_int(char *str, int d);
int				ft_usage(void);
size_t			get_file(const char *name, char **str);
void			print_time(int fd);

#endif