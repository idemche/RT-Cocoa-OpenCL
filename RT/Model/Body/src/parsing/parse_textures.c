/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:52:49 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/01 16:12:23 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		get_number_textures(void)
{
	FILE	*fptr;
	char	c[2048];

	if ((fptr = fopen("number.txt", "r")) == NULL)
	{
		ft_putstr("Error! opening file");
		return (0);
	}
	fscanf(fptr, "%[^\n]", c);
	fclose(fptr);
	return (atoi(c));
}

void	filling_available_texture(t_info *a, int number)
{
	FILE	*fptr;
	char	c[2048];
	int		i;

	i = 0;
	fptr = fopen("textures.txt", "r");
	a->available_texture = (char **)malloc(sizeof(char *) * (number + 1));
	a->available_texture[number] = NULL;
	if (fptr != NULL)
	{
		while (fgets(c, 2048, fptr))
		{
			c[strcspn(c, "\n")] = 0;
			a->available_texture[i] = ft_strdup(c);
			i++;
		}
		fclose(fptr);
	}
}

void	check_was_before(t_info *a, int i, int j, int *was_before)
{
	*was_before = 0;
	while (++j < i)
	{
		if (a->objects[i].albedo_n == a->objects[j].albedo_n)
		{
			*was_before = 1;
			break ;
		}
	}
}

void	get_unique_textures(t_info *a)
{
	int i;
	int k;
	int was_before;

	a->scene->amount_of_albedo_textures = 0;
	a->unique_tex = (int*)malloc(sizeof(int) * a->scene->amount_of_objects);
	i = -1;
	k = -1;
	while (++i < a->scene->amount_of_objects)
	{
		if (a->objects[i].albedo_n >= 0)
		{
			check_was_before(a, i, -1, &was_before);
			if (!was_before)
			{
				a->scene->amount_of_albedo_textures++;
				a->unique_tex[++k] = a->objects[i].albedo_n;
			}
		}
	}
	get_unique_texture_number(a);
}

int		parse_texture(t_info *a)
{
	int		i;
	int		number;

	system("ls textures/ | grep '.png$' | wc -l > number.txt");
	system("ls textures/ | grep '.png$' > textures.txt");
	number = get_number_textures();
	filling_available_texture(a, number);
	check_unique_textures(a, number);
	get_unique_textures(a);
	if (number == 0)
		return (0);
	write_textures(a, -1, -1, -1);
	i = -1;
	while (++i < a->scene->amount_of_objects)
		free(a->texture_names[i]);
	free(a->texture_names);
	i = -1;
	while (++i < number)
		free(a->available_texture[i]);
	free(a->available_texture);
	free(a->unique_tex);
	system("rm number.txt textures.txt");
	return (1);
}
