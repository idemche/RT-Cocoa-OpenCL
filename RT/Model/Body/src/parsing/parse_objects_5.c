/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:53:16 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/21 02:50:03 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	dna_parsing_(t_info *a, int i, t_object *o, t_json_object *d)
{
	int		period;

	period = 2;
	if (!cJSON_IsNumber(d->length) || (o->top = d->length->valuedouble) <= 0.0)
	{
		object_warning(a, i, "invalid length, default 250");
		o->top = 250.0;
	}
	if (!cJSON_IsNumber(d->width) ||
		(o->radius = d->width->valuedouble) <= 0.0)
	{
		object_warning(a, i, "invalid width, default 50");
		o->radius = 50.0;
	}
	if (!cJSON_IsNumber(d->period) ||
		(period = d->period->valueint) < 1 || period > 10)
	{
		object_warning(a, i, "invalid period, default 1");
		period = 2;
	}
	return (period);
}

void		dna_parsing(t_info *a, int i, t_object *o, t_json_scene *js)
{
	t_json_object	d;
	int				period;

	get_object_info(&d, js);
	parse_color(a, i, &o->color, d.color);
	if (!parse_point(&o->point1, d.p1) || !parse_point(&o->dir, d.dir))
		object_error(a, i, "invalid xyz field");
	if (!check_vec3(o->dir))
		object_error(a, i, "invalid dir");
	else
		normalise_vec3(&o->dir);
	if (!cJSON_IsNumber(d.freq) || (o->frequency = d.freq->valueint) < 4)
	{
		object_warning(a, i, "invalid frequency, default 10");
		o->frequency = 10;
	}
	period = dna_parsing_(a, i, o, &d);
	o->k = o->top / (period * o->frequency);
	o->top += o->k;
	o->bot = -o->k;
	o->radius2 = o->k * o->k * 0.15f;
	write_transform_matrix_to_object(o);
	o->edge2 = i_3(2.0f * M_PI / o->frequency, (o->radius - sqrt(o->radius2))
							* 0.5f, (o->radius + 0.01f) * (o->radius + 0.01f));
	o->period = (int)(o->top / o->k);
}

void		heart_parsing(t_info *a, int i, t_object *o, t_json_scene *js)
{
	t_json_object h;

	get_object_info(&h, js);
	if (!parse_point(&o->point1, h.p1) || !parse_point(&o->n, h.n))
		object_error(a, i, "invalid xyz field");
	parse_color(a, i, &o->color, h.color);
	if (!check_vec3(o->n))
		object_error(a, i, "invalid n");
	else
	{
		normalise_vec3(&o->n);
		o->edge0 = cross_prod((fabs(o->n.x) > 1e-6 ?
			i_3(0, 1, 0) : i_3(1, 0, 0)), o->n);
		normalise_vec3(&o->edge0);
		o->edge1 = cross_prod(o->n, o->edge0);
		normalise_vec3(&o->edge1);
	}
	if (!cJSON_IsNumber(h.width) || h.width->valuedouble < 1.0)
	{
		o->radius = 30;
		object_warning(a, i, "invalid width, default 30");
	}
	else
		o->radius = h.width->valuedouble;
}
