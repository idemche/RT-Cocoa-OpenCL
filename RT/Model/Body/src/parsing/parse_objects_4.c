/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:53:16 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/13 01:51:07 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		cone_parsing(t_object *object, t_json_scene *js)
{
	t_json_object		con;

	con.obj = cJSON_GetObjectItemCaseSensitive(js->object, "cone");
	con.dir = cJSON_GetObjectItemCaseSensitive(con.obj, "dir");
	con.p1 = cJSON_GetObjectItemCaseSensitive(con.obj, "pos");
	con.color = cJSON_GetObjectItemCaseSensitive(con.obj, "color");
	con.angle = cJSON_GetObjectItemCaseSensitive(con.obj, "angle");
	con.top = cJSON_GetObjectItemCaseSensitive(con.obj, "top_height");
	con.bot = cJSON_GetObjectItemCaseSensitive(con.obj, "bottom_height");
	parse_color(&object->color, con.color);
	parse_point(&object->point1, con.p1);
	parse_point(&object->dir, con.dir);
	if (!check_vec3(object->dir))
		ft_error("Invalid direction vector of cone");
	normalise_vec3(&object->dir);
	if (!cJSON_IsNumber(con.angle) || !cJSON_IsNumber(con.bot) ||
		!cJSON_IsNumber(con.top) || !(con.angle->valuedouble > EPS) ||
		!(con.angle->valuedouble < 45.01) || !(con.bot->valuedouble >= 0) ||
		!(con.top->valuedouble >= 0))
		ft_error("Cone error");
	object->k = 1 / cos(RAD(con.angle->valuedouble));
	object->bot = con.bot->valuedouble;
	object->top = con.top->valuedouble;
	write_transform_matrix_to_object(object);
}

void		cylinder_parsing(t_object *object, t_json_scene *js)
{
	t_json_object	cyl;

	cyl.obj = cJSON_GetObjectItemCaseSensitive(js->object, "cylinder");
	cyl.color = cJSON_GetObjectItemCaseSensitive(cyl.obj, "color");
	cyl.dir = cJSON_GetObjectItemCaseSensitive(cyl.obj, "dir");
	cyl.p1 = cJSON_GetObjectItemCaseSensitive(cyl.obj, "pos");
	cyl.r = cJSON_GetObjectItemCaseSensitive(cyl.obj, "r");
	cyl.top = cJSON_GetObjectItemCaseSensitive(cyl.obj, "height");
	parse_point(&object->point1, cyl.p1);
	parse_point(&object->dir, cyl.dir);
	parse_color(&object->color, cyl.color);
	if (!check_vec3(object->dir))
		ft_error("Invalid direction vector of cylinder");
	normalise_vec3(&object->dir);
	if (!cJSON_IsNumber(cyl.r) || !cJSON_IsNumber(cyl.top) ||
		!(cyl.r->valuedouble > 0.0) || !(cyl.top->valuedouble > 0.0))
		ft_error("Cylinder error");
	object->radius = cyl.r->valuedouble;
	object->radius2 = object->radius * object->radius;
	object->top = cyl.top->valuedouble;
	object->edge0 = cross_prod(object->dir, (fabs(object->dir.x) > 1e-6 ?
												i_3(0, 1, 0) : i_3(1, 0, 0)));
	object->edge1 = cross_prod(object->dir, object->edge0);
}

void		disk_parsing(t_object *object, t_json_scene *js)
{
	t_json_object	disk;

	disk.obj = cJSON_GetObjectItemCaseSensitive(js->object, "disk");
	disk.p1 = cJSON_GetObjectItemCaseSensitive(disk.obj, "pos");
	disk.dir = cJSON_GetObjectItemCaseSensitive(disk.obj, "dir");
	disk.color = cJSON_GetObjectItemCaseSensitive(disk.obj, "color");
	disk.r = cJSON_GetObjectItemCaseSensitive(disk.obj, "r");
	parse_point(&object->point1, disk.p1);
	parse_point(&object->n, disk.dir);
	parse_color(&object->color, disk.color);
	if (!check_vec3(object->n))
		ft_error("Invalid direction vector of disk");
	normalise_vec3(&object->n);
	if (!cJSON_IsNumber(disk.r) || !(disk.r->valuedouble > 0.0))
		ft_error("Disk radius error");
	object->radius = disk.r->valuedouble;
	object->edge0 = cross_prod(object->n, (fabs(object->n.x) > 1e-6 ?
												i_3(0, 1, 0) : i_3(1, 0, 0)));
	object->edge1 = cross_prod(object->n, object->edge0);
}

void		paraboloid_parsing(t_object *object, t_json_scene *js)
{
	t_json_object	par;

	par.obj = cJSON_GetObjectItemCaseSensitive(js->object, "paraboloid");
	par.k = cJSON_GetObjectItemCaseSensitive(par.obj, "k");
	par.top = cJSON_GetObjectItemCaseSensitive(par.obj, "height");
	par.color = cJSON_GetObjectItemCaseSensitive(par.obj, "color");
	par.dir = cJSON_GetObjectItemCaseSensitive(par.obj, "dir");
	par.p1 = cJSON_GetObjectItemCaseSensitive(par.obj, "pos");
	parse_point(&object->point1, par.p1);
	parse_point(&object->dir, par.dir);
	parse_color(&object->color, par.color);
	if (!check_vec3(object->dir))
		ft_error("Invalid direction vector of paraboloid");
	normalise_vec3(&object->dir);
	if (!cJSON_IsNumber(par.k) || !cJSON_IsNumber(par.top) ||
		!(par.k->valuedouble > 0.0) || !(par.top->valuedouble > 0.0))
		ft_error("Paraboloid k error");
	object->k = par.k->valuedouble;
	object->top = par.top->valuedouble;
}

void		plane_parsing(t_object *object, t_json_scene *js)
{
	t_json_object	pl;

	pl.obj = cJSON_GetObjectItemCaseSensitive(js->object, "plane");
	pl.p1 = cJSON_GetObjectItemCaseSensitive(pl.obj, "point");
	pl.n = cJSON_GetObjectItemCaseSensitive(pl.obj, "norm");
	pl.color = cJSON_GetObjectItemCaseSensitive(pl.obj, "color");
	parse_point(&object->point1, pl.p1);
	parse_point(&object->n, pl.n);
	parse_color(&object->color, pl.color);
	if (!check_vec3(object->n))
		ft_error("Invalid direction vector of plane");
	normalise_vec3(&object->n);
	object->edge0 = cross_prod(object->n, (fabs(object->n.x) > 1e-6 ?
												i_3(0, 1, 0) : i_3(1, 0, 0)));
	normalise_vec3(&object->edge0);
	object->edge1 = cross_prod(object->n, object->edge0);
	normalise_vec3(&object->edge1);
}
