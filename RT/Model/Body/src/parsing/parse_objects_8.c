/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_8.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:53:16 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/19 19:12:02 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static VEC3	get_vector(t_object *o, VEC3 k)
{
	VEC3	res;

	res = add_vec3(o->point1, k);
	res = sub_vec3(res, o->point2);
	normalise_vec3(&res);
	res = mult_3(res, o->top);
	return (res);
}

static void	get_octahedron_info(t_object *o)
{
	VEC3		tmp;

	o->top = o->radius * sqrt(2);
	o->point2 = add_vec3(o->edge0, o->edge2);
	normalise_vec3(&o->point2);
	o->point2 = mult_3(o->point2, o->radius / sqrt(2));
	o->point2 = add_vec3(o->point1, o->point2);
	o->point2 = add_vec3(o->point2, mult_3(o->edge1, -o->radius * 0.5));
	o->a = get_vector(o, mult_3(o->edge0, o->radius * 0.5));
	o->upsilon = get_vector(o, add_vec3(mult_3(o->edge2, o->radius * 0.5),
												mult_3(o->edge0, o->radius)));
	o->b = get_vector(o, mult_3(o->edge2, o->radius * 0.5));
	o->c = get_vector(o, add_vec3(mult_3(o->edge2, o->radius),
										mult_3(o->edge0, o->radius * 0.5)));
	tmp = mult_3(o->edge1, o->top * sqrt(2));
	o->point3 = add_vec3(o->point2, tmp);
	o->n = mult_3(add_vec3(o->point2, o->point3), 0.5);
	o->c2 = dot_3(o->n, o->n);
	o->radius2 = o->radius * o->radius;
}

static void	get_cube_info(t_info *a, int i, t_object *o, t_json_object *t)
{
	parse_color(a, i, &o->color, t->color);
	if (!cJSON_IsNumber(t->length) || t->length->valuedouble < 0)
	{
		o->radius = 300.0;
		object_warning(a, i, "invalid length, default 300");
	}
	else
		o->radius = t->length->valuedouble;
	if (!parse_point(&o->point1, t->p1) || !parse_point(&o->edge0, t->vec1) ||
		!parse_point(&o->edge1, t->vec2))
		object_error(a, i, "invalid xyz field");
	o->edge2 = cross_prod(o->edge0, o->edge1);
	if (!check_vec3(o->edge0) || !check_vec3(o->edge1) ||
														!check_vec3(o->edge2))
	{
		object_error(a, i, "invalid vector configuration");
		return ;
	}
	else
	{
		o->edge1 = cross_prod(o->edge0, o->edge2);
		normalise_vec3(&o->edge0);
		normalise_vec3(&o->edge1);
		normalise_vec3(&o->edge2);
	}
}

void		cubohedron_parsing(t_info *a, int i, t_object *o, t_json_scene *js)
{
	t_json_object	t;

	get_object_info(&t, js);
	get_cube_info(a, i, o, &t);
	get_octahedron_info(o);
}

void		paraboloid_parsing(t_info *a, int i, t_object *o, t_json_scene *js)
{
	t_json_object	par;

	get_object_info(&par, js);
	if (!parse_point(&o->point1, par.p1) || !parse_point(&o->dir, par.dir))
		object_error(a, i, "invalid xyz field");
	parse_color(a, i, &o->color, par.color);
	if (!check_vec3(o->dir))
		object_error(a, i, "invalid direction vector");
	else
		normalise_vec3(&o->dir);
	if (!cJSON_IsNumber(par.k) || (o->k = par.k->valuedouble) < 0.0)
	{
		object_warning(a, i, "invalid k, default 10");
		o->k = 10.0;
	}
	if (!cJSON_IsNumber(par.top) || (o->top = par.top->valuedouble) < 0.0)
	{
		object_warning(a, i, "invalid top, default 100");
		o->top = 100.0;
	}
}
