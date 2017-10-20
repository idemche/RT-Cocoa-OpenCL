/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:53:16 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/20 13:30:55 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	cone_parsing_(t_info *a, int i, t_object *o, t_json_object *con)
{
	if (!cJSON_IsNumber(con->bot) || con->bot->valuedouble < 0)
	{
		object_warning(a, i, "invalid bot, default 300");
		o->bot = 300.0;
	}
	else
		o->bot = con->bot->valuedouble;
	if (!cJSON_IsNumber(con->top) || con->top->valuedouble < 0)
	{
		object_warning(a, i, "invalid top, default 300");
		o->top = 300.0;
	}
	else
		o->top = con->top->valuedouble;
}

void		cone_parsing(t_info *a, int i, t_object *o, t_json_scene *js)
{
	t_json_object		con;

	get_object_info(&con, js);
	parse_color(a, i, &o->color, con.color);
	if (!parse_point(&o->point1, con.p1) || !parse_point(&o->dir, con.dir))
		object_error(a, i, "invalid xyz field");
	if (!check_vec3(o->dir))
		object_error(a, i, "invalid direction vector");
	else
		normalise_vec3(&o->dir);
	if (!cJSON_IsNumber(con.angle) || !(con.angle->valuedouble > EPS) ||
		!(con.angle->valuedouble < 45.01))
	{
		object_warning(a, i, "invalid angle, default 30");
		o->k = 1 / cos(RAD(30.0));
	}
	else
		o->k = 1 / cos(RAD(con.angle->valuedouble));
	cone_parsing_(a, i, o, &con);
	write_transform_matrix_to_object(o);
}

static void	cylinder_parsing_(t_info *a, int i, t_object *o, t_json_object *c)
{
	if (!cJSON_IsNumber(c->r) || !(c->r->valuedouble > 0.0))
	{
		object_warning(a, i, "invalid radius, default 50");
		o->radius = 50.0;
	}
	else
		o->radius = c->r->valuedouble;
	o->radius2 = o->radius * o->radius;
	if (!cJSON_IsNumber(c->top) || c->top->valuedouble < 0)
	{
		object_warning(a, i, "invalid top, default 300");
		o->top = 300.0;
	}
	else
		o->top = c->top->valuedouble;
}

void		cylinder_parsing(t_info *a, int i, t_object *o, t_json_scene *js)
{
	t_json_object	cyl;

	get_object_info(&cyl, js);
	if (!parse_point(&o->point1, cyl.p1) || !parse_point(&o->dir, cyl.dir))
		object_error(a, i, "invalid xyz field");
	parse_color(a, i, &o->color, cyl.color);
	if (!check_vec3(o->dir))
		object_error(a, i, "invalid direction vector");
	else
	{
		normalise_vec3(&o->dir);
		o->edge0 = cross_prod(o->dir, (fabs(o->dir.x) > 1e-6 ?
												i_3(0, 1, 0) : i_3(1, 0, 0)));
		o->edge1 = cross_prod(o->dir, o->edge0);
	}
	cylinder_parsing_(a, i, o, &cyl);
}

void		disk_parsing(t_info *a, int i, t_object *o, t_json_scene *js)
{
	t_json_object	disk;

	get_object_info(&disk, js);
	if (!parse_point(&o->point1, disk.p1) || !parse_point(&o->n, disk.dir))
		object_error(a, i, "invalid xyz field");
	parse_color(a, i, &o->color, disk.color);
	if (!check_vec3(o->n))
		object_error(a, i, "invalid direction vector");
	else
	{
		normalise_vec3(&o->n);
		o->edge0 = cross_prod(o->n, (fabs(o->n.x) > 1e-6 ?
												i_3(0, 1, 0) : i_3(1, 0, 0)));
		o->edge1 = cross_prod(o->n, o->edge0);
	}
	if (!cJSON_IsNumber(disk.r) || !(disk.r->valuedouble > 0.0))
	{
		object_warning(a, i, "invalid radius, default 100");
		o->radius = 100.0;
	}
	else
		o->radius = disk.r->valuedouble;
}
