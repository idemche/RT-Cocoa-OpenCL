/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_9.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:53:16 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/19 19:12:10 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	get_info(t_info *a, int i, t_object *o, t_json_object *t)
{
	if (!parse_point(&o->point1, t->p1) || !parse_point(&o->edge0, t->vec2) ||
		!parse_point(&o->dir, t->vec1))
		object_error(a, i, "invalid xyz field");
	o->edge1 = cross_prod(o->dir, o->edge0);
	if (!cJSON_IsNumber(t->length) || t->length->valuedouble < 0)
	{
		o->top = 300.0;
		object_warning(a, i, "invalid length, default 300");
	}
	else
		o->top = t->length->valuedouble;
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

void		ring_parsing_(t_info *a, int i, t_object *o, t_json_object *r)
{
	if (!cJSON_IsNumber(r->top) || r->top->valuedouble < 0)
	{
		object_warning(a, i, "invalid top, default 35");
		o->top = 35.0;
	}
	else
		o->top = r->top->valuedouble;
	if (!cJSON_IsNumber(r->r) || r->r->valuedouble < 0 ||
		r->r->valuedouble > o->radius)
	{
		object_warning(a, i, "invalid r, default 0.95 * r_big");
		o->k = 0.95 * o->radius;
	}
	else
		o->k = r->r->valuedouble;
}

void		ring_parsing(t_info *a, int i, t_object *o, t_json_scene *js)
{
	t_json_object	r;

	get_object_info(&r, js);
	parse_color(a, i, &o->color, r.color);
	if (!parse_point(&o->point1, r.p1) || !parse_point(&o->dir, r.dir))
		object_error(a, i, "invalid xyz field");
	if (!check_vec3(o->dir))
		object_error(a, i, "invalid direction vector");
	else
		normalise_vec3(&o->dir);
	if (!cJSON_IsNumber(r.r_big) || !(r.r_big->valuedouble > 0.0))
	{
		object_warning(a, i, "invalid r_big, default 150");
		o->radius = 150.0;
	}
	else
		o->radius = r.r_big->valuedouble;
	o->radius2 = o->radius * o->radius;
	ring_parsing_(a, i, o, &r);
}

void		plane_parsing(t_info *a, int i, t_object *o, t_json_scene *js)
{
	t_json_object	pl;

	get_object_info(&pl, js);
	if (!parse_point(&o->point1, pl.p1) || !parse_point(&o->n, pl.n))
		object_error(a, i, "invalid xyz field");
	parse_color(a, i, &o->color, pl.color);
	if (!check_vec3(o->n))
		object_error(a, i, "invalid direction vector");
	else
	{
		normalise_vec3(&o->n);
		o->edge0 = cross_prod(o->n, (fabs(o->n.x) > 1e-6 ?
												i_3(0, 1, 0) : i_3(1, 0, 0)));
		normalise_vec3(&o->edge0);
		o->edge1 = cross_prod(o->n, o->edge0);
		normalise_vec3(&o->edge1);
	}
}
