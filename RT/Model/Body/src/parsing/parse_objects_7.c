/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_7.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:53:16 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/19 19:10:32 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static VEC3	get_info(t_info *a, int i, t_object *o, t_json_object *t)
{
	VEC3 result;

	parse_color(a, i, &o->color, t->color);
	if (!parse_point(&o->point1, t->p1) || !parse_point(&o->dir, t->vec1) ||
		!parse_point(&o->edge0, t->vec2))
		object_error(a, i, "invalid xyz field");
	if (!cJSON_IsNumber(t->length) || (o->top = t->length->valuedouble) <= 0.0)
	{
		object_warning(a, i, "invalid length, default 250");
		o->top = 250.0;
	}
	if (!check_vec3(o->edge0) || !check_vec3(o->dir))
		object_error(a, i, "invalid vectors");
	normalise_vec3(&o->dir);
	normalise_vec3(&o->edge0);
	o->edge0 = mult_3(o->edge0, o->top);
	result = cross_prod(o->dir, o->edge0);
	if (!check_vec3(result))
		object_error(a, i, "invalid config");
	else
		normalise_vec3(&result);
	return (result);
}

static void	get_circumsphere(t_object *o)
{
	VEC3 tmp;

	o->radius = sqrt(0.375) * o->top;
	o->radius2 = o->radius * o->radius;
	tmp = add_vec3(o->edge0, o->edge1);
	normalise_vec3(&tmp);
	tmp = mult_3(tmp, o->top / sqrt(3));
	o->edge2 = add_vec3(tmp, mult_3(o->dir, sqrt(2.0 / 3.0) * o->top));
	o->upsilon = add_vec3(add_vec3(o->point1, tmp), mult_3(o->dir,
													sqrt(6) / 12.0 * o->top));
	o->c2 = dot_3(o->upsilon, o->upsilon);
}

void		tetrahedron_parsing(t_info *a, int i, t_object *o, t_json_scene *j)
{
	t_json_object	t;
	VEC3			tmp;

	get_object_info(&t, j);
	tmp = get_info(a, i, o, &t);
	tmp = mult_3(tmp, o->top);
	o->edge1 = add_vec3(mult_3(o->edge0, 0.5), tmp);
	normalise_vec3(&o->edge1);
	o->edge1 = mult_3(o->edge1, o->top);
	get_circumsphere(o);
}

void		star_parsing(t_info *a, int i, t_object *o, t_json_scene *js)
{
	t_json_object	t;
	VEC3			tmp;

	get_object_info(&t, js);
	tmp = get_info(a, i, o, &t);
	o->b = add_vec3(o->point1, mult_3(tmp, o->top / sqrt(3)));
	o->b = add_vec3(o->b, mult_3(o->dir, o->top / sqrt(6)));
	tmp = mult_3(tmp, o->top * sqrt(3) * 0.5);
	o->edge1 = add_vec3(mult_3(o->edge0, 0.5), tmp);
	o->n = sub_vec3(mult_3(o->edge0, 0.5), tmp);
	tmp = add_vec3(o->edge0, o->n);
	normalise_vec3(&tmp);
	tmp = mult_3(tmp, o->top / sqrt(3));
	o->a = add_vec3(tmp, mult_3(o->dir, -sqrt(2.0 / 3.0) * o->top));
	o->c = add_vec3(add_vec3(o->b, tmp), mult_3(o->dir, -sqrt(6) / 12.0 *
																	o->top));
	get_circumsphere(o);
}

void		parse_texture_config(t_info *a, int i, t_json_scene *js,
															t_json_material *m)
{
	if (ft_strcmp(a->texture_names[i], "None"))
	{
		m->scale = cJSON_GetObjectItem(js->object, "Scale coefficient");
		m->shift = cJSON_GetObjectItem(js->object, "Shift coefficient");
		if (!cJSON_IsNumber(m->scale) || !cJSON_IsNumber(m->shift) ||
			m->scale->valuedouble < 0 || m->scale->valuedouble > 32 ||
			m->shift->valuedouble < 0 || m->shift->valuedouble > 1)
		{
			object_warning(a, i, "invalid scale and shit fields, default 0:1");
			a->objects[i].tex_shift = 0.0f;
			a->objects[i].tex_scale = 1;
		}
		else
		{
			a->objects[i].tex_scale = m->scale->valuedouble;
			a->objects[i].tex_shift = m->shift->valuedouble;
		}
	}
	else
	{
		a->objects[i].tex_shift = 0.0f;
		a->objects[i].tex_scale = 0;
	}
}
