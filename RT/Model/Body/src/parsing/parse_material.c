/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:53:05 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/18 20:20:32 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_material	get_material_type(t_info *a, int i, char *material)
{
	if (!ft_strcmp(material, "DIFF"))
		return (DIFF);
	else if (!ft_strcmp(material, "SPEC"))
		return (SPEC);
	else if (!ft_strcmp(material, "REFR"))
		return (REFR);
	else if (!ft_strcmp(material, "GLOSSY"))
		return (GLOSSY);
	else if (!ft_strcmp(material, "GLOSSY_REFR"))
		return (GLOSSY_REFR);
	else if (!ft_strcmp(material, "TRANSPARENT"))
		return (TRANSPARENT);
	else
	{
		object_warning(a, i, "invalid material type, default DIFF");
		return (DIFF);
	}
}

static void			parse_glossy_refr(t_info *a, t_json_scene *js, int i,
														t_json_material *m)
{
	if (a->objects[i].material == GLOSSY ||
		a->objects[i].material == GLOSSY_REFR)
	{
		m->g = cJSON_GetObjectItemCaseSensitive(js->object, "glossiness");
		if (!cJSON_IsNumber(m->g) || m->g->valuedouble < 0)
		{
			object_warning(a, i, "invalid glossiness, default 0");
			a->objects[i].glossiness = 0.0;
		}
		else
			a->objects[i].glossiness = m->g->valuedouble;
	}
	if (a->objects[i].material == REFR ||
		a->objects[i].material == GLOSSY_REFR)
	{
		m->refr_index = cJSON_GetObjectItemCaseSensitive(js->object, "n");
		if (!cJSON_IsNumber(m->refr_index) || m->refr_index->valuedouble < 1.0)
		{
			object_warning(a, i, "invalid n (refractive index), default 2.5");
			a->objects[i].refr_index = 2.5;
		}
		else
			a->objects[i].refr_index = m->refr_index->valuedouble;
	}
}

static void			parse_material_2(t_info *a, int i, t_json_scene *js,
															t_json_material *m)
{
	a->objects[i].material = get_material_type(a, i, m->material->valuestring);
	parse_glossy_refr(a, js, i, m);
	if (a->objects[i].material != DIFF)
	{
		m->kd = cJSON_GetObjectItemCaseSensitive(js->object, "kd");
		if (!cJSON_IsNumber(m->kd) || m->kd->valuedouble < 0
							|| m->kd->valuedouble > 1)
		{
			object_warning(a, i, "invalid kd coefficient, default 0");
			a->objects[i].kd = 0;
		}
		else
			a->objects[i].kd = m->kd->valuedouble;
	}
}

static void			parse_transparent(t_info *a, int i, t_json_material m,
															t_json_scene *js)
{
	m.absorption = cJSON_GetObjectItemCaseSensitive(js->object, "absorption");
	m.abs_r = cJSON_GetObjectItemCaseSensitive(m.absorption, "r");
	m.abs_g = cJSON_GetObjectItemCaseSensitive(m.absorption, "g");
	m.abs_b = cJSON_GetObjectItemCaseSensitive(m.absorption, "b");
	if (!cJSON_IsNumber(m.abs_r) || !cJSON_IsNumber(m.abs_g) ||
		!cJSON_IsNumber(m.abs_b))
	{
		object_warning(a, i, "invalid absorption field, default (0, 0, 0)");
		a->objects[i].absorption = i_3(0, 0, 0);
	}
	else
		a->objects[i].absorption = i_3(m.abs_r->valuedouble,
										m.abs_g->valuedouble,
										m.abs_b->valuedouble);
}

void				parse_material(t_info *a, int i, t_json_scene *js)
{
	t_json_material m;

	parse_texture_config(a, i, js, &m);
	m.u = cJSON_GetObjectItemCaseSensitive(js->object, "Speed");
	if (m.u)
	{
		if (!parse_point(&a->objects[i].upsilon, m.u))
			object_error(a, i, "invalid speed field");
	}
	else
		a->objects[i].upsilon = i_3(0, 0, 0);
	m.emission = cJSON_GetObjectItemCaseSensitive(js->object, "emission");
	m.material = cJSON_GetObjectItemCaseSensitive(js->object, "material");
	if (a->objects[i].type == SPHERE)
		parse_emission(a, &a->objects[i].emission, m.emission);
	if (m.material)
		parse_material_2(a, i, js, &m);
	else
		a->objects[i].material = DIFF;
	if (a->objects[i].material == DIFF)
		a->objects[i].kd = 1;
	if (a->objects[i].material == TRANSPARENT)
		parse_transparent(a, i, m, js);
}
