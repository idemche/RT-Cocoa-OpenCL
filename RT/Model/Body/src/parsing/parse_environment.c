/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_environment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:53:05 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/20 13:26:11 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		write_float3(t_info *a, t_uch *tmp, int w, int h)
{
	int		x;
	int		y;
	int		k;
	int		k4;

	a->environment_map = (cl_float3*)malloc(sizeof(cl_float3) * w * h);
	y = -1;
	while (++y < h)
	{
		x = -1;
		while (++x < w)
		{
			k = x + y * w;
			k4 = (x + y * w) << 2;
			a->environment_map[k].x = (float)(tmp[k4 + 0]) / 255.0f;
			a->environment_map[k].y = (float)(tmp[k4 + 1]) / 255.0f;
			a->environment_map[k].z = (float)(tmp[k4 + 2]) / 255.0f;
		}
	}
}

static void		get_type(t_info *a, t_json_env *e)
{
	t_uch		*tmp;
	t_uint		w;
	t_uint		h;

	if (ft_strstr(e->m->valuestring, ".hdr"))
	{
		if ((a->environment_map = read_hdr(e->m->valuestring,
			&a->scene->env_map_w, &a->scene->env_map_h)) != NULL)
			a->scene->radiance_env_map = 1;
	}
	else if (ft_strstr(e->m->valuestring, ".png"))
	{
		if (!lodepng_decode32_file(&tmp, &w, &h, e->m->valuestring))
		{
			write_float3(a, tmp, w, h);
			a->scene->radiance_env_map = 0;
			a->scene->env_map_w = (int)w;
			a->scene->env_map_h = (int)h;
			free(tmp);
		}
	}
}

void			parse_environment_map(t_info *a, t_json_scene *js)
{
	t_json_env	e;

	e.e = cJSON_GetObjectItemCaseSensitive(js->root, "environment");
	e.m = cJSON_GetObjectItemCaseSensitive(e.e, "map");
	if (!e.m || a->is_validating)
		a->scene->env_map = 0;
	else
	{
		if (!cJSON_IsString(e.m))
			warning(a, "invalid environment map field, wtf how?");
		else
		{
			if (ft_strcmp(e.m->valuestring, "None"))
			{
				get_type(a, &e);
				if (!a->environment_map)
					warning(a, "invalid environment map file");
				else
					a->scene->env_map = 1;
			}
			else
				a->scene->env_map = 0;
		}
	}
}

static void		validate_env_parameters(t_json_env *e, t_info *a)
{
	if (!cJSON_IsNumber(e->spppc) || e->spppc->valueint < 1)
	{
		warning(a, "invalid spp per call field, default value 1");
		a->spp_per_call = 1;
	}
	else
		a->spp_per_call = e->spppc->valueint;
	if (e->ambient)
		parse_emission(a, &a->scene->ambient, e->ambient);
	else
		a->scene->ambient = i_3(0, 0, 0);
	if (e->p_l_e && e->p_l_d)
	{
		parse_emission(a, &a->scene->parallel_emis, e->p_l_e);
		if (!parse_point(&a->scene->parallel_dir, e->p_l_d))
			scene_error(a, "missing parallel light direction");
		if (!check_vec3(a->scene->parallel_dir))
			scene_error(a, "invalid dir vector of parallel light");
	}
	if (!e->p_l_e)
		a->scene->parallel_emis = i_3(4, 4, 4);
	if (!e->p_l_d)
		a->scene->parallel_dir = i_3(-1, -1, -1);
	normalise_vec3(&a->scene->parallel_dir);
}

void			environment_parsing(t_info *a, t_json_scene *js)
{
	t_json_env	e;

	e.e = cJSON_GetObjectItemCaseSensitive(js->root, "environment");
	e.ambient = cJSON_GetObjectItemCaseSensitive(e.e, "ambient light");
	e.spppc = cJSON_GetObjectItemCaseSensitive(e.e, "spp per call");
	e.p_l_e = cJSON_GetObjectItem(e.e, "parallel light emission");
	e.p_l_d = cJSON_GetObjectItem(e.e, "parallel light direction");
	validate_env_parameters(&e, a);
	e.gamma = cJSON_GetObjectItemCaseSensitive(e.e, "gamma");
	if (!cJSON_IsNumber(e.gamma) || e.gamma->valuedouble < 1.0f)
	{
		warning(a, "invalid gamma value, default 2.2");
		a->scene->gamma = 2.2;
	}
	else
		a->scene->gamma = e.gamma->valuedouble;
}
