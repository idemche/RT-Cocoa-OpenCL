/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:53:11 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/17 02:26:52 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		sphere_parsing(t_object *object, t_json_scene *js)
{
	t_json_object	sp;

	sp.obj = cJSON_GetObjectItemCaseSensitive(js->object, "sphere");
	sp.color = cJSON_GetObjectItemCaseSensitive(sp.obj, "color");
	sp.p1 = cJSON_GetObjectItemCaseSensitive(sp.obj, "pos");
	sp.r = cJSON_GetObjectItemCaseSensitive(sp.obj, "r");
	parse_point(&object->point1, sp.p1);
	object->c2 = dot_3(object->point1, object->point1);
	parse_color(&object->color, sp.color);
	if (!cJSON_IsNumber(sp.r) || !(sp.r->valuedouble > 0.0))
	{
		ft_warning("invalid sphere radius, default 100");
		object->radius = 100.0;
	}
	else
		object->radius = sp.r->valuedouble;
	object->radius2 = object->radius * object->radius;
}

void		triangle_parsing(t_object *object, t_json_scene *js)
{
	t_json_object		tr;
	VEC3				e1;
	VEC3				e2;

	tr.obj = cJSON_GetObjectItemCaseSensitive(js->object, "triangle");
	tr.p1 = cJSON_GetObjectItemCaseSensitive(tr.obj, "point1");
	tr.p2 = cJSON_GetObjectItemCaseSensitive(tr.obj, "point2");
	tr.p3 = cJSON_GetObjectItemCaseSensitive(tr.obj, "point3");
	tr.color = cJSON_GetObjectItemCaseSensitive(tr.obj, "color");
	parse_point(&object->point1, tr.p1);
	parse_point(&object->point2, tr.p2);
	parse_point(&object->point3, tr.p3);
	parse_color(&object->color, tr.color);
	e1 = sub_vec3(object->point2, object->point1);
	e2 = sub_vec3(object->point3, object->point1);
	object->n = cross_prod(e1, e2);
	if (!check_vec3(object->n))
		ft_error("Triangle error: points belong to one line");
	normalise_vec3(&object->n);
	object->edge0 = e1;
	object->edge1 = sub_vec3(object->point3, object->point2);
	object->edge2 = sub_vec3(object->point1, object->point3);
}

void		cube_parsing(t_object *object, t_json_scene *js)
{
	t_json_object	b;

	b.obj = cJSON_GetObjectItemCaseSensitive(js->object, "cube");
	b.p1 = cJSON_GetObjectItemCaseSensitive(b.obj, "point");
	b.vec1 = cJSON_GetObjectItemCaseSensitive(b.obj, "vec1");
	b.vec2 = cJSON_GetObjectItemCaseSensitive(b.obj, "vec2");
	b.length = cJSON_GetObjectItemCaseSensitive(b.obj, "length");
	b.color = cJSON_GetObjectItemCaseSensitive(b.obj, "color");
	parse_color(&object->color, b.color);
	if (!cJSON_IsNumber(b.length) || b.length->valuedouble < 0)
		ft_error("Invalid box length");
	parse_point(&object->point1, b.p1);
	parse_point(&object->edge0, b.vec1);
	parse_point(&object->edge1, b.vec2);
	if (!check_vec3(object->edge0) || !check_vec3(object->edge1))
		ft_error("Invalid cube vector");
	object->edge2 = cross_prod(object->edge0, object->edge1);
	if (!check_vec3(object->edge2))
		ft_error("Invalid cube configuration");
	object->edge1 = cross_prod(object->edge0, object->edge2);
	normalise_vec3(&object->edge0);
	normalise_vec3(&object->edge1);
	normalise_vec3(&object->edge2);
	object->radius = b.length->valuedouble;
}

void		bocal_parsing(t_object *object, t_json_scene *js)
{
	t_json_object	b;

	b.obj = cJSON_GetObjectItemCaseSensitive(js->object, "bocal");
	b.top = cJSON_GetObjectItemCaseSensitive(b.obj, "height");
	b.dir = cJSON_GetObjectItemCaseSensitive(b.obj, "dir");
	b.p1 = cJSON_GetObjectItemCaseSensitive(b.obj, "point");
	b.color = cJSON_GetObjectItemCaseSensitive(b.obj, "color");
	parse_point(&object->dir, b.dir);
	parse_point(&object->point1, b.p1);
	parse_color(&object->color, b.color);
	if (!check_vec3(object->dir))
		ft_error("Invalid bocal dir vector");
	normalise_vec3(&object->dir);
	if (!cJSON_IsNumber(b.top) || b.top->valuedouble < 0)
	{
		ft_warning("invalid bocal height, default 250");
		object->top = 250.0;
	}
	else
		object->top = b.top->valuedouble;
}
