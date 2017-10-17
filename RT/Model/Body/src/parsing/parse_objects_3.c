/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:53:11 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/17 20:06:32 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	box_parsing_(t_object *object, VEC3 tmp)
{
	normalise_vec3(&object->edge0);
	object->edge1 = cross_prod(object->edge0, tmp);
	normalise_vec3(&object->edge1);
	object->n = cross_prod(object->edge1, object->edge0);
	if (!check_vec3(object->n))
		ft_error("Box error: points belong to one line");
	normalise_vec3(&object->n);
	object->edge0 = mult_3(object->edge0, object->radius);
	object->edge1 = mult_3(object->edge1, object->radius);
	object->point2 = add_vec3(object->point1, object->edge0);
	object->point3 = add_vec3(object->point2, object->edge1);
	object->edge2 = add_vec3(object->point1, object->edge1);
}

void		box_parsing(t_object *object, t_json_scene *js)
{
	t_json_object		b;
	VEC3				tmp;

	b.obj = cJSON_GetObjectItemCaseSensitive(js->object, "box");
	b.p1 = cJSON_GetObjectItemCaseSensitive(b.obj, "point");
	b.vec1 = cJSON_GetObjectItemCaseSensitive(b.obj, "vec1");
	b.vec2 = cJSON_GetObjectItemCaseSensitive(b.obj, "vec2");
	b.length = cJSON_GetObjectItemCaseSensitive(b.obj, "length");
	if (!cJSON_IsNumber(b.length) || b.length->valuedouble < 0)
	{
		ft_warning("invalid box length, default 250");
		object->radius = 250.0;
	}
	else
		object->radius = b.length->valuedouble;
	b.color = cJSON_GetObjectItemCaseSensitive(b.obj, "color");
	parse_point(&object->point1, b.p1);
	parse_point(&object->edge0, b.vec1);
	parse_point(&tmp, b.vec2);
	parse_color(&object->color, b.color);
	if (!check_vec3(object->edge0) || !check_vec3(tmp))
		ft_error("Invalid box vectors error");
	box_parsing_(object, tmp);
}

void		mob_parsing(t_object *object, t_json_scene *js)
{
	t_json_object m;

	m.obj = cJSON_GetObjectItemCaseSensitive(js->object, "moebius");
	m.p1 = cJSON_GetObjectItemCaseSensitive(m.obj, "pos");
	m.color = cJSON_GetObjectItemCaseSensitive(m.obj, "color");
	m.r = cJSON_GetObjectItemCaseSensitive(m.obj, "radius");
	m.width = cJSON_GetObjectItemCaseSensitive(m.obj, "width");
	parse_color(&object->color, m.color);
	parse_point(&object->point1, m.p1);
	if (!cJSON_IsNumber(m.r) || m.r->valuedouble < 0.0 ||
		!cJSON_IsNumber(m.width) || m.width->valuedouble < 0.0)
	{
		ft_warning("invalid moebius config, default radius=200, width=50");
		object->radius = 200.0;
		object->radius2 = 50.0;
	}
	else
	{
		object->radius = m.r->valuedouble;
		object->radius2 = m.width->valuedouble;
	}
}

void		torus_parsing(t_object *object, t_json_scene *js)
{
	t_json_object t;

	t.obj = cJSON_GetObjectItemCaseSensitive(js->object, "torus");
	t.p1 = cJSON_GetObjectItemCaseSensitive(t.obj, "pos");
	t.dir = cJSON_GetObjectItemCaseSensitive(t.obj, "dir");
	t.color = cJSON_GetObjectItemCaseSensitive(t.obj, "color");
	parse_color(&object->color, t.color);
	parse_point(&object->point1, t.p1);
	parse_point(&object->dir, t.dir);
	if (!check_vec3(object->dir))
		ft_error("Invalid torus direction vector");
	normalise_vec3(&object->dir);
	t.r_big = cJSON_GetObjectItemCaseSensitive(t.obj, "R");
	t.r = cJSON_GetObjectItemCaseSensitive(t.obj, "r");
	if (!cJSON_IsNumber(t.r) || t.r->valuedouble <= 0 ||
		!cJSON_IsNumber(t.r_big) || t.r_big->valuedouble <= 0)
	{
		object->radius = 250.0;
		object->radius2 = 40.0;
	}
	else
	{
		object->radius = t.r_big->valuedouble;
		object->radius2 = t.r->valuedouble;
	}
}

void		elipsoid_parsing(t_object *object, t_json_scene *js)
{
	t_json_object	e;

	e.obj = cJSON_GetObjectItemCaseSensitive(js->object, "elipsoid");
	e.p1 = cJSON_GetObjectItemCaseSensitive(e.obj, "point");
	e.r = cJSON_GetObjectItemCaseSensitive(e.obj, "radius sum");
	e.k = cJSON_GetObjectItemCaseSensitive(e.obj, "focal distance");
	e.dir = cJSON_GetObjectItemCaseSensitive(e.obj, "dir");
	e.color = cJSON_GetObjectItemCaseSensitive(e.obj, "color");
	parse_point(&object->point1, e.p1);
	parse_color(&object->color, e.color);
	parse_point(&object->dir, e.dir);
	if (!check_vec3(object->dir))
		ft_error("Elipsoid error: dir couldn't be a zero vector");
	normalise_vec3(&object->dir);
	if (!cJSON_IsNumber(e.r) || !cJSON_IsNumber(e.k) || e.k->valuedouble < 0
		|| e.r->valuedouble < 1)
		ft_error("Elipsoid error: invalid radius sum or focal distance");
	object->radius = e.r->valuedouble;
	object->k = e.k->valuedouble;
	if (object->k >= object->radius)
		ft_error("radius sum must be greater than focal distance");
	object->radius2 = object->radius * object->radius;
}
