/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:53:16 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/17 11:31:26 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	validate_dna(t_object *object, t_json_object *d)
{
	parse_color(&object->color, d->color);
	parse_point(&object->point1, d->p1);
	parse_point(&object->dir, d->dir);
	if (!check_vec3(object->dir))
		ft_error("DNA direction could not be a zero vector");
	normalise_vec3(&object->dir);
	if (!cJSON_IsNumber(d->period) || !cJSON_IsNumber(d->length) ||
		!cJSON_IsNumber(d->freq) || !cJSON_IsNumber(d->width) ||
		d->period->valueint < 1 || d->period->valueint > 10 ||
		d->freq->valueint < 4 || d->length->valuedouble <= 0.0 ||
		d->width->valuedouble <= 0.0)
	{
		ft_warning("invalid DNA config, default values goes in");
		object->radius = 50.0;
		object->period = 1;
		object->frequency = 10;
		object->top = 250.0;
	}
	else
	{
		object->radius = d->width->valuedouble;
		object->period = d->period->valueint;
		object->frequency = d->freq->valuedouble;
		object->top = d->length->valuedouble;
	}
}

void		dna_parsing(t_object *object, t_json_scene *js)
{
	t_json_object	d;

	d.obj = cJSON_GetObjectItemCaseSensitive(js->object, "dna");
	d.period = cJSON_GetObjectItemCaseSensitive(d.obj, "periods");
	d.freq = cJSON_GetObjectItemCaseSensitive(d.obj, "frequency");
	d.length = cJSON_GetObjectItemCaseSensitive(d.obj, "total length");
	d.p1 = cJSON_GetObjectItemCaseSensitive(d.obj, "start point");
	d.dir = cJSON_GetObjectItemCaseSensitive(d.obj, "direction");
	d.width = cJSON_GetObjectItemCaseSensitive(d.obj, "width");
	d.color = cJSON_GetObjectItemCaseSensitive(d.obj, "color");
	validate_dna(object, &d);
	object->k = object->top / (object->period * object->frequency);
	object->top += object->k;
	object->bot = -object->k;
	object->radius2 = object->k * object->k * 0.15f;
	write_transform_matrix_to_object(object);
}

void		heart_parsing(t_object *object, t_json_scene *js)
{
	t_json_object h;

	h.obj = cJSON_GetObjectItemCaseSensitive(js->object, "heart");
	h.p1 = cJSON_GetObjectItemCaseSensitive(h.obj, "point");
	h.n = cJSON_GetObjectItemCaseSensitive(h.obj, "normal");
	h.width = cJSON_GetObjectItemCaseSensitive(h.obj, "size");
	parse_point(&object->point1, h.p1);
	h.p1 = cJSON_GetObjectItemCaseSensitive(h.obj, "color");
	parse_color(&object->color, h.p1);
	parse_point(&object->n, h.n);
	if (!check_vec3(object->n))
		ft_error("Heart's normal could not be a zero vector");
	normalise_vec3(&object->n);
	if (!cJSON_IsNumber(h.width) || h.width->valuedouble < 1.0)
		ft_error("Invalid size of heart");
	object->radius = h.width->valuedouble;
	object->edge0 = cross_prod((fabs(object->n.x) > 1e-6 ?
		i_3(0, 1, 0) : i_3(1, 0, 0)), object->n);
	normalise_vec3(&object->edge0);
	object->edge1 = cross_prod(object->n, object->edge0);
	normalise_vec3(&object->edge1);
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
		ft_error("Object type error");
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
