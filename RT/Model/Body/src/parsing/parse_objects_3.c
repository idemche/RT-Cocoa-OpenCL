/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:53:11 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/20 13:35:13 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	box_parsing_(t_info *a, int i, t_object *o, VEC3 tmp)
{
	normalise_vec3(&o->edge0);
	o->edge1 = cross_prod(o->edge0, tmp);
	normalise_vec3(&o->edge1);
	o->n = cross_prod(o->edge1, o->edge0);
	if (!check_vec3(o->n))
		object_error(a, i, "points belong to one line");
	else
	{
		normalise_vec3(&o->n);
		o->edge0 = mult_3(o->edge0, o->radius);
		o->edge1 = mult_3(o->edge1, o->radius);
		o->point2 = add_vec3(o->point1, o->edge0);
		o->point3 = add_vec3(o->point2, o->edge1);
		o->edge2 = add_vec3(o->point1, o->edge1);
	}
}

void		box_parsing(t_info *a, int i, t_object *o, t_json_scene *js)
{
	t_json_object		b;
	VEC3				tmp;

	get_object_info(&b, js);
	if (!cJSON_IsNumber(b.length) || (o->radius = b.length->valuedouble) < 0)
	{
		object_warning(a, i, "invalid box length, default 250");
		o->radius = 250.0;
	}
	if (!parse_point(&o->point1, b.p1) || !parse_point(&o->edge0, b.vec1) ||
		!parse_point(&tmp, b.vec2))
		object_error(a, i, "invalid xyz field");
	parse_color(a, i, &o->color, b.color);
	if (!check_vec3(o->edge0) || !check_vec3(tmp))
		object_error(a, i, "invalid vectors");
	else
		box_parsing_(a, i, o, tmp);
}

void		mob_parsing(t_info *a, int i, t_object *o, t_json_scene *js)
{
	t_json_object m;

	get_object_info(&m, js);
	parse_color(a, i, &o->color, m.color);
	if (!parse_point(&o->point1, m.p1) || !parse_point(&o->dir, m.dir))
		object_error(a, i, "invalid xyz");
	if (!check_vec3(o->dir))
		object_error(a, i, "invalid direction vector");
	else
		normalise_vec3(&o->dir);
	if (!cJSON_IsNumber(m.r) || (o->radius = m.r->valuedouble) < 0.0)
	{
		object_warning(a, i, "invalid radius, default 200");
		o->radius = 200.0;
	}
	if (!cJSON_IsNumber(m.width) || (o->radius2 = m.width->valuedouble) < 0.0)
	{
		object_warning(a, i, "invalid width, default 50");
		o->radius2 = 50.0;
	}
	write_transform_matrix_to_object(o);
}

void		torus_parsing(t_info *a, int i, t_object *o, t_json_scene *js)
{
	t_json_object t;

	get_object_info(&t, js);
	parse_color(a, i, &o->color, t.color);
	if (!parse_point(&o->point1, t.p1) || !parse_point(&o->dir, t.dir))
		object_error(a, i, "invalid xyz field");
	if (!check_vec3(o->dir))
		object_error(a, i, "invalid direction vector");
	else
		normalise_vec3(&o->dir);
	if (!cJSON_IsNumber(t.r) || (o->radius2 = t.r->valuedouble) <= 0)
	{
		object_warning(a, i, "invalid r, default 40");
		o->radius2 = 40;
	}
	if (!cJSON_IsNumber(t.r_big) || (o->radius = t.r_big->valuedouble) <= 0)
	{
		object_warning(a, i, "invalid r_big, default 250");
		o->radius = 250.0;
	}
}

void		elipsoid_parsing(t_info *a, int i, t_object *o, t_json_scene *js)
{
	t_json_object	e;

	get_object_info(&e, js);
	parse_color(a, i, &o->color, e.color);
	if (!parse_point(&o->point1, e.p1) || !parse_point(&o->dir, e.dir))
		object_error(a, i, "invalid xyz field");
	if (!check_vec3(o->dir))
		object_error(a, i, "invalid dir");
	else
		normalise_vec3(&o->dir);
	if (!cJSON_IsNumber(e.r) || (o->radius = e.r->valuedouble) < 1)
	{
		object_warning(a, i, "invalid radius sum, default 300");
		o->radius = 300.0;
	}
	if (!cJSON_IsNumber(e.k) || (o->k = e.k->valuedouble) < 0)
	{
		o->k = 275.0;
		object_warning(a, i, "invalid focal distance, default 275");
	}
	if (o->k >= o->radius)
		object_error(a, i, "radius sum must be greater than focal distance");
	o->radius2 = o->radius * o->radius;
}
