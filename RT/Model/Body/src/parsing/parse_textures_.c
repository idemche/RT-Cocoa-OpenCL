/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures_.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:52:49 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/01 16:06:43 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		init_tex(t_tmp_tex *t, t_info *a)
{
	if ((t->rgba_albedo = (t_uch*)malloc(sizeof(t_uch) *
		a->scene->amount_of_albedo_textures * 16777216)) == NULL)
		ft_error("malloc error");
	if ((t->rgba_normal = (t_uch*)malloc(sizeof(t_uch) *
		a->scene->amount_of_albedo_textures * 16777216)) == NULL)
		ft_error("malloc error");
}

void		get_paths(t_info *a, t_tmp_tex *t, int i)
{
	size_t	len;
	char	*png;

	len = strlen(a->available_texture[a->unique_tex[i]]);
	t->tex_path_albedo = (char*)malloc(len + 10);
	t->tex_path_normal = (char*)malloc(len + 15);
	strlcat(t->tex_path_albedo, "textures/", len + 10);
	strlcat(t->tex_path_albedo, a->available_texture[a->unique_tex[i]],
																	len + 10);
	strlcat(t->tex_path_normal, t->tex_path_albedo, len + 15);
	png = strstr(t->tex_path_normal, ".png");
	strcpy(png, "_norm");
	strcpy(&png[5], ".png");
}

void		generate_pictures(t_info *a, t_tmp_tex *t, int i)
{
	get_paths(a, t, i);
	if (lodepng_decode32_file(&t->tmp_rgba, &t->width, &t->height,
														t->tex_path_albedo))
		ft_error("Missing file for albedo texture");
	if (t->width != 2048 || t->height != 2048)
		ft_error("invalid texture");
	memcpy(t->rgba_albedo + 16777216 * i * sizeof(t_uch), t->tmp_rgba,
													16777216 * sizeof(t_uch));
	free(t->tmp_rgba);
	if (lodepng_decode32_file(&t->tmp_rgba, &t->width, &t->height,
														t->tex_path_normal))
		ft_error("Missing file for normal texture");
	if (t->width != 2048 || t->height != 2048)
		ft_error("invalid texture");
	memcpy(t->rgba_normal + 16777216 * i * sizeof(t_uch), t->tmp_rgba,
											16777216 * sizeof(t_uch));
	free(t->tmp_rgba);
	free(t->tex_path_normal);
	free(t->tex_path_albedo);
}

static void	write_to_array(t_info *a, int k, t_tmp_tex t)
{
	int k4;

	k4 = k << 2;
	a->albedo_textures[k].x = (float)(t.rgba_albedo[k4 + 0]) / 255.0f;
	a->albedo_textures[k].y = (float)(t.rgba_albedo[k4 + 1]) / 255.0f;
	a->albedo_textures[k].z = (float)(t.rgba_albedo[k4 + 2]) / 255.0f;
	a->normal_textures[k].x = (float)(t.rgba_normal[k4 + 0]) / 127.5f - 1.0f;
	a->normal_textures[k].y = (float)(t.rgba_normal[k4 + 1]) / 127.5f - 1.0f;
	a->normal_textures[k].z = ((float)(t.rgba_normal[k4 + 2]) - 128.0f) /
																		127.0f;
}

void		write_textures(t_info *a, int i, int x, int y)
{
	t_tmp_tex	t;
	int			k;

	init_tex(&t, a);
	while (++i < a->scene->amount_of_albedo_textures)
		generate_pictures(a, &t, i);
	t.height *= a->scene->amount_of_albedo_textures;
	a->albedo_textures = (VEC3*)malloc(sizeof(VEC3) * t.width * t.height);
	a->normal_textures = (VEC3*)malloc(sizeof(VEC3) * t.width * t.height);
	while (++y < (int)t.height)
	{
		x = -1;
		while (++x < (int)t.width)
		{
			k = x + y * t.width;
			write_to_array(a, k, t);
		}
	}
	free(t.rgba_albedo);
	free(t.rgba_normal);
}
