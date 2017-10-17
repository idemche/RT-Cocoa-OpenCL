/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:44:38 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/17 02:10:27 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
		ft_putstr("open failed: ");
		ft_error((char*)name);
	}
	fseek(file, 0, SEEK_END);
	len = ftell(file);
	fseek(file, 0, SEEK_SET);
	if (!(*str = (char*)malloc(sizeof(char) * (len + 1))))
		ft_error("get_file(): malloc error");
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

void		ft_error_int(char *str, int d)
{
	printf("%s%d\n", str, d);
	exit(1);
}

void		ft_warning(char *str)
{
	ft_putstr("Warning: ");
	ft_putstr(str);
	ft_putchar('\n');
}
