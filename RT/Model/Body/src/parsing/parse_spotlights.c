/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spotlights.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:52:58 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/20 13:59:56 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		ibasis(t_info *a, cl_int i, t_json_lt *lt)
{
	VEC3	u;

	if (!cJSON_IsNumber(lt->radius) || !(lt->radius->valuedouble >= 0))
	{
		warning(a, "invalid spotlight radius, default 50");
		a->spotlights[i].radius = 50.0;
	}
	else
		a->spotlights[i].radius = lt->radius->valuedouble;
	if (!a->scene_is_valid)
		return ;
	a->spotlights[i].w = a->spotlights[i].dir;
	u = cross_prod((fabs(a->spotlights[i].w.x) > 1e-6) ? i_3(0.f, 1.f, 0.f) :
									i_3(1.f, 0.f, 0.f), a->spotlights[i].w);
	normalise_vec3(&u);
	a->spotlights[i].u = u;
	a->spotlights[i].v = cross_prod(a->spotlights[i].w, a->spotlights[i].u);
	a->spotlights[i].u = mult_3(a->spotlights[i].u,
													a->spotlights[i].radius);
	a->spotlights[i].v = mult_3(a->spotlights[i].v,
													a->spotlights[i].radius);
	a->spotlights[i].w = mult_3(a->spotlights[i].w,
													a->spotlights[i].radius);
}

static void		parse_light(t_info *a, t_json_scene *js, t_json_lt *lt, int i)
{
	lt->pos = cJSON_GetObjectItemCaseSensitive(js->light, "point");
	lt->dir = cJSON_GetObjectItemCaseSensitive(js->light, "dir");
	lt->alpha = cJSON_GetObjectItemCaseSensitive(js->light, "alpha");
	lt->emission = cJSON_GetObjectItemCaseSensitive(js->light, "emission");
	lt->radius = cJSON_GetObjectItemCaseSensitive(js->light, "radius");
	if (!parse_point(&a->spotlights[i].pos, lt->pos) ||
		!parse_point(&a->spotlights[i].dir, lt->dir))
		scene_error(a, "invalid spotlight xyz field");
	if (!check_vec3(a->spotlights[i].dir))
		scene_error(a, "invalid spotlight dir");
	else
		normalise_vec3(&a->spotlights[i].dir);
	if (!cJSON_IsNumber(lt->alpha) || !(lt->alpha->valuedouble >= 0.0f) ||
											!(lt->alpha->valuedouble <= 30.0f))
	{
		warning(a, "invalid spotlight angle, default 15");
		a->spotlights[i].alpha = 15 * M_PI / 180.0f;
	}
	else
		a->spotlights[i].alpha = lt->alpha->valuedouble * M_PI / 180.0f;
	parse_emission(a, &(a->spotlights[i].emission), lt->emission);
	ibasis(a, i, lt);
}

void			light_parsing(t_info *a, t_json_scene *js)
{
	cl_int			i;
	t_json_lt		lt;

	js->spotlights = cJSON_GetObjectItemCaseSensitive(js->root, "spotlights");
	if (cJSON_IsArray(js->spotlights))
	{
		a->scene->amount_of_spotlights = cJSON_GetArraySize(js->spotlights);
		a->spotlights = (t_spotlight*)malloc(sizeof(t_spotlight) *
										a->scene->amount_of_spotlights);
		i = -1;
		while (++i < a->scene->amount_of_spotlights)
		{
			js->light = cJSON_GetArrayItem(js->spotlights, i);
			parse_light(a, js, &lt, i);
		}
	}
	else
		a->scene->amount_of_spotlights = 0;
}
