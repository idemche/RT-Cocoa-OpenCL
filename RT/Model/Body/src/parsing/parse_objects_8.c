/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_8.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:53:16 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/17 20:10:54 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static VEC3		get_vector(t_object *o, VEC3 k)
{
	VEC3	res;

	res = add_vec3(o->point1, k);
	res = sub_vec3(res, o->point2);
	normalise_vec3(&res);
	res = mult_3(res, o->top);
	return (res);
}

static void		get_octahedron_info(t_object *o)
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

static void		get_cube_info(t_object *o, t_json_object *t)
{
	t->p1 = cJSON_GetObjectItemCaseSensitive(t->obj, "point");
	t->vec1 = cJSON_GetObjectItemCaseSensitive(t->obj, "vec1");
	t->vec2 = cJSON_GetObjectItemCaseSensitive(t->obj, "vec2");
	t->length = cJSON_GetObjectItemCaseSensitive(t->obj, "length");
	t->color = cJSON_GetObjectItemCaseSensitive(t->obj, "color");
	parse_color(&o->color, t->color);
	if (!cJSON_IsNumber(t->length) || t->length->valuedouble < 0)
		ft_error("Invalid box length");
	parse_point(&o->point1, t->p1);
	parse_point(&o->edge0, t->vec1);
	parse_point(&o->edge1, t->vec2);
	o->edge2 = cross_prod(o->edge0, o->edge1);
	if (!check_vec3(o->edge0) || !check_vec3(o->edge1) ||
														!check_vec3(o->edge2))
		ft_error("Invalid cube configuration");
	o->edge1 = cross_prod(o->edge0, o->edge2);
	normalise_vec3(&o->edge0);
	normalise_vec3(&o->edge1);
	normalise_vec3(&o->edge2);
	o->radius = t->length->valuedouble;
}

void			cubohedron_parsing(t_object *object, t_json_scene *js)
{
	t_json_object	t;

	t.obj = cJSON_GetObjectItemCaseSensitive(js->object, "cubohedron");
	get_cube_info(object, &t);
	get_octahedron_info(object);
}
