/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_9.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:53:16 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/18 14:56:42 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	get_info(t_info *a, int i, t_object *o, t_json_object *t)
{
	if (!parse_point(&o->edge0, t->vec2) || parse_point(&o->dir, t->vec1) ||
		parse_point(&o->point1, t->p1))
		object_error(a, i, "invalid xyz field");
	o->edge1 = cross_prod(o->dir, o->edge0);
	if (!check_vec3(o->edge0) || !check_vec3(o->dir) || !check_vec3(o->edge1))
	{
		object_error(a, i, "invalid vector configuration");
		return ;
	}
	else
	{
		o->edge0 = cross_prod(o->dir, o->edge1);
		normalise_vec3(&o->dir);
		normalise_vec3(&o->edge0);
		normalise_vec3(&o->edge1);
		o->edge0 = mult_3(o->edge0, o->top);
		o->edge1 = mult_3(o->edge1, o->top);
	}
	if (!cJSON_IsNumber(t->length) || t->length->valuedouble < 0)
	{
		o->top = 300.0;
		object_warning(a, i, "invalid length, default 300");
	}
	else
		o->top = t->length->valuedouble;
}

void		octahedron_parsing(t_info *a, int i, t_object *o, t_json_scene *js)
{
	t_json_object	t;
	VEC3			diag;
	double			diag_len;

	get_object_info(&t, js);
	parse_color(a, i, &o->color, t.color);
	get_info(a, i, o, &t);
	diag = add_vec3(o->edge0, o->edge1);
	normalise_vec3(&diag);
	diag = mult_3(diag, o->top * sqrt(2));
	o->point2 = add_vec3(o->point1, diag);
	diag = mult_3(diag, 0.5);
	diag_len = o->top / sqrt(2);
	o->edge2 = add_vec3(diag, mult_3(o->dir, diag_len));
	o->a = add_vec3(diag, mult_3(o->dir, -diag_len));
	o->point3 = add_vec3(o->point1, diag);
	o->c2 = dot_3(o->point3, o->point3);
	o->radius = diag_len;
	o->radius2 = diag_len * diag_len;
}
