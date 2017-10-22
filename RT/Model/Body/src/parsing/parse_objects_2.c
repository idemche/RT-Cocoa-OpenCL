/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:53:11 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/18 20:20:50 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		sphere_parsing(t_info *a, int i, t_object *o, t_json_scene *js)
{
	t_json_object	sp;

	get_object_info(&sp, js);
	if (!parse_point(&o->point1, sp.p1))
		object_error(a, i, "invalid point1");
	else
		o->c2 = dot_3(o->point1, o->point1);
	parse_color(a, i, &o->color, sp.color);
	if (!cJSON_IsNumber(sp.r) || !(sp.r->valuedouble > 0.0))
	{
		object_warning(a, i, "invalid radius, default 100");
		o->radius = 100.0;
	}
	else
		o->radius = sp.r->valuedouble;
	o->radius2 = o->radius * o->radius;
}

void		triangle_parsing(t_info *a, int i, t_object *o, t_json_scene *js)
{
	t_json_object		tr;
	VEC3				e1;

	get_object_info(&tr, js);
	if (!tr.p1 || !tr.p2 || !tr.p3)
		object_error(a, i, "missing point fields");
	else
	{
		if (!parse_point(&o->point1, tr.p1) || !parse_point(&o->point2, tr.p2)
			|| !parse_point(&o->point3, tr.p3))
			object_error(a, i, "invalid point");
		else
		{
			e1 = sub_vec3(o->point2, o->point1);
			o->n = cross_prod(e1, sub_vec3(o->point3, o->point1));
			if (!check_vec3(o->n))
				object_error(a, i, "points belong to one line");
			else
				normalise_vec3(&o->n);
			o->edge0 = e1;
			o->edge1 = sub_vec3(o->point3, o->point2);
			o->edge2 = sub_vec3(o->point1, o->point3);
		}
	}
	parse_color(a, i, &o->color, tr.color);
}

void		cube_parsing(t_info *a, int i, t_object *o, t_json_scene *js)
{
	t_json_object	b;

	get_object_info(&b, js);
	parse_color(a, i, &o->color, b.color);
	if (!cJSON_IsNumber(b.length) || b.length->valuedouble < 0)
	{
		o->radius = 100.0;
		object_warning(a, i, "invalid box length, default 100");
	}
	else
		o->radius = b.length->valuedouble;
	if (!parse_point(&o->point1, b.p1) || !parse_point(&o->edge0, b.vec1) ||
		!parse_point(&o->edge1, b.vec2))
		object_error(a, i, "invalid xyz fields");
	if (!check_vec3(o->edge0) || !check_vec3(o->edge1))
		object_error(a, i, "zero vectors");
	o->edge2 = cross_prod(o->edge0, o->edge1);
	if (!check_vec3(o->edge2))
		object_error(a, i, "invalid cube configuration");
	o->edge1 = cross_prod(o->edge0, o->edge2);
	normalise_vec3(&o->edge0);
	normalise_vec3(&o->edge1);
	normalise_vec3(&o->edge2);
}

void		bocal_parsing(t_info *a, int i, t_object *o, t_json_scene *js)
{
	t_json_object	b;

	get_object_info(&b, js);
	if (!parse_point(&o->dir, b.dir) || !parse_point(&o->point1, b.p1))
		object_error(a, i, "invalid xyz field");
	parse_color(a, i, &o->color, b.color);
	if (!check_vec3(o->dir))
		object_error(a, i, "invalid dir vector");
	else
		normalise_vec3(&o->dir);
	if (!cJSON_IsNumber(b.top) || b.top->valuedouble < 0)
	{
		object_warning(a, i, "invalid bocal height, default 250");
		o->top = 250.0;
	}
	else
		o->top = b.top->valuedouble;
}
