/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures__.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:52:49 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/05 16:01:33 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		get_unique_texture_number(t_info *a)
{
	int i;
	int k;

	i = -1;
	while (++i < a->scene->amount_of_objects)
	{
		k = -1;
		while (++k < a->scene->amount_of_albedo_textures)
		{
			if (a->objects[i].albedo_n == a->unique_tex[k])
			{
				a->objects[i].albedo_n = k;
				break ;
			}
		}
	}
}

static int	check_predefined_texture_names(t_info *a, int i)
{
	if (!ft_strcmp(a->texture_names[i], "None"))
		a->objects[i].albedo_n = -1;
	else if (!ft_strcmp(a->texture_names[i], "Perlin"))
		a->objects[i].albedo_n = PERLIN;
	else if (!ft_strcmp(a->texture_names[i], "Normal"))
		a->objects[i].albedo_n = NORMAL;
	else if (!ft_strcmp(a->texture_names[i], "Checkerboard"))
		a->objects[i].albedo_n = CHECKERBOARD;
	else if (!ft_strcmp(a->texture_names[i], "Truechecker"))
		a->objects[i].albedo_n = TRUE_CHECKER;
	else
		return (0);
	return (1);
}

void		check_unique_textures(t_info *a, int number)
{
	int	i;
	int	j;

	i = -1;
	while (++i < a->scene->amount_of_objects)
	{
		j = -1;
		if (check_predefined_texture_names(a, i))
			continue ;
		while (++j < number)
		{
			if (!ft_strcmp(a->texture_names[i], a->available_texture[j]))
			{
				a->objects[i].albedo_n = j;
				break ;
			}
		}
		if (j == number)
			a->objects[i].albedo_n = -1;
	}
}
