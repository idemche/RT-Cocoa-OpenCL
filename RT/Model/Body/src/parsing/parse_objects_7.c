/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_7.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:53:16 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/17 20:10:32 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		get_info(t_object *object, t_json_object *t)
{
	t->p1 = cJSON_GetObjectItemCaseSensitive(t->obj, "point");
	t->vec1 = cJSON_GetObjectItemCaseSensitive(t->obj, "up vector");
	t->length = cJSON_GetObjectItemCaseSensitive(t->obj, "length");
	t->vec2 = cJSON_GetObjectItemCaseSensitive(t->obj, "right vector");
	t->color = cJSON_GetObjectItemCaseSensitive(t->obj, "color");
	parse_color(&object->color, t->color);
	parse_point(&object->point1, t->p1);
	parse_point(&object->dir, t->vec1);
	parse_point(&object->edge0, t->vec2);
	if (!check_vec3(object->edge0) || !check_vec3(object->dir))
		ft_error("Invalid vectors");
	normalise_vec3(&object->dir);
	normalise_vec3(&object->edge0);
	if (!cJSON_IsNumber(t->length) || t->length->valuedouble <= 0.0)
		ft_error("Invalid length");
	object->top = t->length->valuedouble;
}

static void		get_circumsphere(t_object *object)
{
	VEC3 tmp;

	object->radius = sqrt(0.375) * object->top;
	object->radius2 = object->radius * object->radius;
	tmp = add_vec3(object->edge0, object->edge1);
	normalise_vec3(&tmp);
	tmp = mult_3(tmp, object->top / sqrt(3));
	object->edge2 = add_vec3(tmp, mult_3(object->dir, sqrt(2.0 / 3.0) *
																object->top));
	object->upsilon = add_vec3(add_vec3(object->point1, tmp),
							mult_3(object->dir, sqrt(6) / 12.0 * object->top));
	object->c2 = dot_3(object->upsilon, object->upsilon);
}

void			tetrahedron_parsing(t_object *object, t_json_scene *js)
{
	t_json_object	t;
	VEC3			tmp;

	t.obj = cJSON_GetObjectItemCaseSensitive(js->object, "tetrahedron");
	get_info(object, &t);
	object->edge0 = mult_3(object->edge0, object->top);
	tmp = cross_prod(object->dir, object->edge0);
	normalise_vec3(&tmp);
	tmp = mult_3(tmp, object->top);
	object->edge1 = add_vec3(mult_3(object->edge0, 0.5), tmp);
	normalise_vec3(&object->edge1);
	object->edge1 = mult_3(object->edge1, object->top);
	get_circumsphere(object);
}

void			star_parsing(t_object *object, t_json_scene *js)
{
	t_json_object	t;
	VEC3			tmp;

	t.obj = cJSON_GetObjectItemCaseSensitive(js->object,
													"stellated octahedron");
	get_info(object, &t);
	object->edge0 = mult_3(object->edge0, object->top);
	tmp = cross_prod(object->dir, object->edge0);
	normalise_vec3(&tmp);
	object->b = add_vec3(object->point1, mult_3(tmp, object->top / sqrt(3)));
	object->b = add_vec3(object->b, mult_3(object->dir, object->top /
																	sqrt(6)));
	tmp = mult_3(tmp, object->top * sqrt(3) * 0.5);
	object->edge1 = add_vec3(mult_3(object->edge0, 0.5), tmp);
	object->n = sub_vec3(mult_3(object->edge0, 0.5), tmp);
	tmp = add_vec3(object->edge0, object->n);
	normalise_vec3(&tmp);
	tmp = mult_3(tmp, object->top / sqrt(3));
	object->a = add_vec3(tmp, mult_3(object->dir, -sqrt(2.0 / 3.0) *
																object->top));
	object->c = add_vec3(add_vec3(object->b, tmp), mult_3(object->dir,
											-sqrt(6) / 12.0 * object->top));
	get_circumsphere(object);
}

void			parse_texture_config(t_info *a, int i, t_json_scene *js,
															t_json_material *m)
{
	if (ft_strcmp(a->texture_names[i], "None"))
	{
		m->scale = cJSON_GetObjectItem(js->object, "Scale coefficient");
		m->shift = cJSON_GetObjectItem(js->object, "Shift coefficient");
		if (!cJSON_IsNumber(m->scale) || !cJSON_IsNumber(m->shift) ||
			m->scale->valueint < 1 || m->scale->valueint > 32 ||
			m->shift->valuedouble < 0 || m->shift->valuedouble > 1)
		{
			ft_warning("invalid scale and shit fields, default 0:1");
			a->objects[i].tex_shift = 0.0f;
			a->objects[i].tex_scale = 1;
		}
		else
		{
			a->objects[i].tex_scale = m->scale->valueint;
			a->objects[i].tex_shift = m->shift->valuedouble;
		}
	}
	else
	{
		a->objects[i].tex_shift = 0.0f;
		a->objects[i].tex_scale = 0;
	}
}
