/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_6.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:53:16 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/17 20:08:06 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_negative_cyl(t_object *object, t_json_object *b)
{
	cl_float3	edge0;
	cl_float3	edge1;
	cl_float3	edge2;

	object->edge1 = cross_prod(object->edge0, object->edge2);
	object->radius = b->length->valuedouble;
	normalise_vec3(&object->edge0);
	normalise_vec3(&object->edge1);
	normalise_vec3(&object->edge2);
	object->dir = object->edge2;
	if (object->radius2 == 0.0f)
		object->radius2 = 0.225f * object->radius;
	edge0 = mult_3(object->edge0, object->radius * 0.5f);
	edge1 = mult_3(object->edge1, object->radius * 0.5f);
	edge2 = mult_3(object->edge2, object->radius * 0.025f);
	object->point2 = add_vec3(object->point1, edge0);
	object->point2 = add_vec3(object->point2, edge1);
	object->point2 = sub_vec3(object->point2, edge2);
	object->top = object->radius * 1.05f;
}

void		cubehole_parsing(t_object *object, t_json_scene *js)
{
	t_json_object	b;

	b.obj = cJSON_GetObjectItemCaseSensitive(js->object, "cubehole");
	b.p1 = cJSON_GetObjectItemCaseSensitive(b.obj, "point");
	b.vec1 = cJSON_GetObjectItemCaseSensitive(b.obj, "vec1");
	b.vec2 = cJSON_GetObjectItemCaseSensitive(b.obj, "vec2");
	b.length = cJSON_GetObjectItemCaseSensitive(b.obj, "length");
	b.color = cJSON_GetObjectItemCaseSensitive(b.obj, "color");
	parse_color(&object->color, b.color);
	parse_point(&object->point1, b.p1);
	parse_point(&object->edge0, b.vec1);
	parse_point(&object->edge1, b.vec2);
	b.r = cJSON_GetObjectItemCaseSensitive(b.obj, "hole radius");
	if (!cJSON_IsNumber(b.r) || b.r->valuedouble > b.length->valuedouble * 0.5f
		|| b.r->valuedouble < 0)
		ft_error("Invalid hole radius value");
	object->radius2 = b.r->valuedouble;
	if (!cJSON_IsNumber(b.length) || b.length->valuedouble < 0)
		ft_error("Invalid cubehole length");
	if (!check_vec3(object->edge0) || !check_vec3(object->edge1))
		ft_error("Invalid cubehole vector");
	object->edge2 = cross_prod(object->edge0, object->edge1);
	if (!check_vec3(object->edge2))
		ft_error("Invalid cubehole configuration");
	init_negative_cyl(object, &b);
}
