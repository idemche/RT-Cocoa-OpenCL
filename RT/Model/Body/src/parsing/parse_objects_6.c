/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_6.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:53:16 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/19 15:26:43 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_negative_cyl(t_info *a, int i, t_object *o)
{
	cl_float3	edge0;

	if (!check_vec3(o->edge0) || !check_vec3(o->edge1))
	{
		object_error(a, i, "invalid vectors");
		return ;
	}
	o->edge2 = cross_prod(o->edge0, o->edge1);
	if (!check_vec3(o->edge2))
	{
		object_error(a, i, "invalid vector configuration");
		return ;
	}
	o->edge1 = cross_prod(o->edge0, o->edge2);
	normalise_vec3(&o->edge0);
	normalise_vec3(&o->edge1);
	normalise_vec3(&o->edge2);
	o->dir = o->edge2;
	edge0 = mult_3(o->edge0, o->radius * 0.5f);
	o->point2 = add_vec3(o->point1, edge0);
	edge0 = mult_3(o->edge1, o->radius * 0.5f);
	o->point2 = add_vec3(o->point2, edge0);
	edge0 = mult_3(o->edge2, o->radius * 0.025f);
	o->point2 = sub_vec3(o->point2, edge0);
}

void		cubehole_parsing(t_info *a, int i, t_object *o, t_json_scene *js)
{
	t_json_object	b;

	get_object_info(&b, js);
	parse_color(a, i, &o->color, b.color);
	if (!parse_point(&o->point1, b.p1) || !parse_point(&o->edge0, b.vec1) ||
		!parse_point(&o->edge1, b.vec2))
		object_error(a, i, "invalid xyz field");
	if (!cJSON_IsNumber(b.length) || b.length->valuedouble < 0)
	{
		o->radius = 300.0;
		object_warning(a, i, "invalid length, default 300");
	}
	else
		o->radius = b.length->valuedouble;
	b.r = cJSON_GetObjectItemCaseSensitive(b.obj, "r");
	if (!cJSON_IsNumber(b.r) || b.r->valuedouble > o->radius * 0.5f
		|| b.r->valuedouble <= 0)
	{
		o->radius2 = 0.225 * o->radius;
		object_warning(a, i, "invalid hole radius, default 0.225*length");
	}
	else
		o->radius2 = b.r->valuedouble;
	o->top = o->radius * 1.05f;
	init_negative_cyl(a, i, o);
}
