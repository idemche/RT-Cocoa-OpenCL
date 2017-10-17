/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_9.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:53:16 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/17 20:11:08 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		get_info(t_object *o, t_json_object *t)
{
	t->p1 = cJSON_GetObjectItemCaseSensitive(t->obj, "point");
	t->vec1 = cJSON_GetObjectItemCaseSensitive(t->obj, "up vector");
	t->vec2 = cJSON_GetObjectItemCaseSensitive(t->obj, "right vector");
	t->length = cJSON_GetObjectItemCaseSensitive(t->obj, "length");
	t->color = cJSON_GetObjectItemCaseSensitive(t->obj, "color");
	parse_color(&o->color, t->color);
	parse_point(&o->edge0, t->vec2);
	parse_point(&o->dir, t->vec1);
	parse_point(&o->point1, t->p1);
	o->edge1 = cross_prod(o->dir, o->edge0);
	if (!check_vec3(o->edge0) || !check_vec3(o->dir) ||
														!check_vec3(o->edge1))
		ft_error("Invalid octahedron vectors");
	o->edge0 = cross_prod(o->dir, o->edge1);
	normalise_vec3(&o->dir);
	normalise_vec3(&o->edge0);
	normalise_vec3(&o->edge1);
	if (!cJSON_IsNumber(t->length) || t->length->valuedouble <= 0.0)
		ft_error("Invalid octahedron length");
	o->top = t->length->valuedouble;
	o->edge0 = mult_3(o->edge0, o->top);
	o->edge1 = mult_3(o->edge1, o->top);
}

void			octahedron_parsing(t_object *object, t_json_scene *js)
{
	t_json_object	t;
	VEC3			diag;
	double			diag_len;

	t.obj = cJSON_GetObjectItemCaseSensitive(js->object, "octahedron");
	get_info(object, &t);
	diag = add_vec3(object->edge0, object->edge1);
	normalise_vec3(&diag);
	diag = mult_3(diag, object->top * sqrt(2));
	object->point2 = add_vec3(object->point1, diag);
	diag = mult_3(diag, 0.5);
	diag_len = object->top / sqrt(2);
	object->edge2 = add_vec3(diag, mult_3(object->dir, diag_len));
	object->a = add_vec3(diag, mult_3(object->dir, -diag_len));
	object->point3 = add_vec3(object->point1, diag);
	object->c2 = dot_3(object->point3, object->point3);
	object->radius = diag_len;
	object->radius2 = diag_len * diag_len;
}
