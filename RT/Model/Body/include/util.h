/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:44:38 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/19 19:18:30 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include "rt.h"

typedef unsigned char	t_uch;
typedef unsigned int	t_uint;
typedef struct s_info	t_info;
typedef struct s_cl		t_cl;

void			ft_error(char *str);
void			ft_warning(char *str);
int				ft_usage(void);
size_t			get_file(const char *name, char **str);
void			print_time(int fd);

#endif
