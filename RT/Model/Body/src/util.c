/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:44:38 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/19 19:14:45 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		print_time(int fd)
{
	time_t		timer;
	char		buffer[26];
	struct tm	*tm_info;

	time(&timer);
	tm_info = localtime(&timer);
	strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
	ft_putendl_fd(buffer, fd);
}

int			ft_usage(void)
{
	ft_putstr("Usage:\n");
	ft_putstr("As client: ./RT 'ip' 'last/****'\n");
	ft_putstr("To validate scene enter: ./RT 'pathToScene' 'validate'\n");
	exit(-2);
}

size_t		get_file(const char *name, char **str)
{
	FILE	*file;
	size_t	len;

	if (!(file = fopen(name, "r")))
	{
		ft_putstr("get_file(): fail to open ");
		ft_putendl((char*)name);
		return (0);
	}
	fseek(file, 0, SEEK_END);
	len = ftell(file);
	fseek(file, 0, SEEK_SET);
	*str = (char*)malloc(sizeof(char) * (len + 1));
	fread(*str, len, 1, file);
	(*str)[len] = '\0';
	fclose(file);
	return (len);
}

void		ft_error(char *str)
{
	ft_putstr(str);
	exit(1);
}

void		ft_warning(char *str)
{
	ft_putstr("Warning: ");
	ft_putstr(str);
	ft_putchar('\n');
}
