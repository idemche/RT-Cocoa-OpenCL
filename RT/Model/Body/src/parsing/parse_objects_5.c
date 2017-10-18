/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:53:16 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/18 14:54:37 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	dna_parsing_(t_info *a, int i, t_object *o, t_json_object *d)
{
	if (!cJSON_IsNumber(d->period) ||
		d->period->valueint < 1 || d->period->valueint > 10)
	{
		object_warning(a, i, "invalid period, default 1");
		o->period = 1;
	}
	else
		o->period = d->period->valueint;
	if (!cJSON_IsNumber(d->length) || d->length->valuedouble <= 0.0)
	{
		object_warning(a, i, "invalid length, default 250");
		o->top = 250.0;
	}
	else
		o->top = d->length->valuedouble;
	if (!cJSON_IsNumber(d->width) || d->width->valuedouble <= 0.0)
	{
		object_warning(a, i, "invalid width, default 50");
		o->radius = 50.0;
	}
	else
		o->radius = d->width->valuedouble;
}

void		dna_parsing(t_info *a, int i, t_object *o, t_json_scene *js)
{
	t_json_object	d;

	get_object_info(&d, js);
	parse_color(a, i, &o->color, d.color);
	if (!parse_point(&o->point1, d.p1) || !parse_point(&o->dir, d.dir))
		object_error(a, i, "invalid xyz field");
	if (!check_vec3(o->dir))
		object_error(a, i, "invalid dir");
	else
		normalise_vec3(&o->dir);
	if (!cJSON_IsNumber(d.freq) || d.freq->valueint < 4)
	{
		object_warning(a, i, "invalid frequency, default 10");
		o->frequency = 10;
	}
	else
		o->frequency = d.freq->valuedouble;
	dna_parsing_(a, i, o, &d);
	o->k = o->top / (o->period * o->frequency);
	o->top += o->k;
	o->bot = -o->k;
	o->radius2 = o->k * o->k * 0.15f;
	write_transform_matrix_to_object(o);
}

void		heart_parsing(t_info *a, int i, t_object *o, t_json_scene *js)
{
	t_json_object h;

	get_object_info(&h, js);
	if (!parse_point(&o->point1, h.p1) || !parse_point(&o->n, h.n))
		object_error(a, i, "invalid xyz field");
	parse_color(a, i, &o->color, h.p1);
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

static void	anti_norminette(t_info *a, cl_int i, char *type)
{
	if (!ft_strcmp(type, "MOEBIUS"))
		a->objects[i].type = MOEBIUS;
	else if (!ft_strcmp(type, "TORUS"))
		a->objects[i].type = TORUS;
	else if (!ft_strcmp(type, "ELIPSOID"))
		a->objects[i].type = ELIPSOID;
	else if (!ft_strcmp(type, "DNA"))
		a->objects[i].type = DNA;
	else if (!ft_strcmp(type, "HEART"))
		a->objects[i].type = HEART;
	else if (!ft_strcmp(type, "CUBEHOLE"))
		a->objects[i].type = CUBEHOLE;
	else if (!ft_strcmp(type, "TETRAHEDRON"))
		a->objects[i].type = TETRAHEDRON;
	else if (!ft_strcmp(type, "STELLATED OCTAHEDRON"))
		a->objects[i].type = STAR;
	else if (!ft_strcmp(type, "OCTAHEDRON"))
		a->objects[i].type = OCTAHEDRON;
	else if (!ft_strcmp(type, "CUBOHEDRON"))
		a->objects[i].type = CUBOHEDRON;
	else
		object_error(a, i, "unknown o type");
}

void		get_object_type(t_info *a, cl_int i, char *type)
{
	if (!ft_strcmp(type, "SPHERE"))
		a->objects[i].type = SPHERE;
	else if (!ft_strcmp(type, "PLANE"))
		a->objects[i].type = PLANE;
	else if (!ft_strcmp(type, "CYLINDER"))
		a->objects[i].type = CYLINDER;
	else if (!ft_strcmp(type, "CONE"))
		a->objects[i].type = CONE;
	else if (!ft_strcmp(type, "PARABOLOID"))
		a->objects[i].type = PARABOLOID;
	else if (!ft_strcmp(type, "DISK"))
		a->objects[i].type = DISK;
	else if (!ft_strcmp(type, "TRIANGLE"))
		a->objects[i].type = TRIANGLE;
	else if (!ft_strcmp(type, "CUBE"))
		a->objects[i].type = CUBE;
	else if (!ft_strcmp(type, "BOX"))
		a->objects[i].type = BOX;
	else if (!ft_strcmp(type, "BOCAL"))
		a->objects[i].type = BOCAL;
	else
		anti_norminette(a, i, type);
}
