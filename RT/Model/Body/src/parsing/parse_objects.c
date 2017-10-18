/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:53:16 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/18 02:35:49 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	norm_please(t_info *a, int i, t_json_scene *js)
{
	if (a->objects[i].type == TORUS)
		torus_parsing(a, i, &(a->objects[i]), js);
	else if (a->objects[i].type == ELIPSOID)
		elipsoid_parsing(a, i, &(a->objects[i]), js);
	else if (a->objects[i].type == DNA)
		dna_parsing(a, i, &(a->objects[i]), js);
	else if (a->objects[i].type == HEART)
		heart_parsing(a, i, &(a->objects[i]), js);
	else if (a->objects[i].type == CUBEHOLE)
		cubehole_parsing(a, i, &(a->objects[i]), js);
	else if (a->objects[i].type == TETRAHEDRON)
		tetrahedron_parsing(a, i, &(a->objects[i]), js);
	else if (a->objects[i].type == STAR)
		star_parsing(a, i, &(a->objects[i]), js);
	else if (a->objects[i].type == OCTAHEDRON)
		octahedron_parsing(a, i, &(a->objects[i]), js);
	else if (a->objects[i].type == CUBOHEDRON)
		cubohedron_parsing(a, i, &(a->objects[i]), js);
}

static void	goto_parsing(t_info *a, int i, t_json_scene *js)
{
	if (a->objects[i].type == SPHERE)
		sphere_parsing(a, i, &(a->objects[i]), js);
	else if (a->objects[i].type == PLANE)
		plane_parsing(a, i, &(a->objects[i]), js);
	else if (a->objects[i].type == CYLINDER)
		cylinder_parsing(a, i, &(a->objects[i]), js);
	else if (a->objects[i].type == CONE)
		cone_parsing(a, i, &(a->objects[i]), js);
	else if (a->objects[i].type == PARABOLOID)
		paraboloid_parsing(a, i, &(a->objects[i]), js);
	else if (a->objects[i].type == DISK)
		disk_parsing(a, i, &(a->objects[i]), js);
	else if (a->objects[i].type == TRIANGLE)
		triangle_parsing(a, i, &(a->objects[i]), js);
	else if (a->objects[i].type == CUBE)
		cube_parsing(a, i, &(a->objects[i]), js);
	else if (a->objects[i].type == BOX)
		box_parsing(a, i, &(a->objects[i]), js);
	else if (a->objects[i].type == BOCAL)
		bocal_parsing(a, i, &(a->objects[i]), js);
	else if (a->objects[i].type == MOEBIUS)
		mob_parsing(a, i, &(a->objects[i]), js);
	else
		norm_please(a, i, js);
}

static void	init_objects_(t_info *a, int i)
{
	a->objects[i].radius2 = 1.0f;
	a->objects[i].bot = 0.0f;
	a->objects[i].top = 0.0f;
	a->objects[i].k = 0.0f;
	a->objects[i].c2 = 0.0f;
	a->objects[i].glossiness = 0.0f;
	a->objects[i].kd = 0.0f;
	a->objects[i].refr_index = 0.0f;
	a->objects[i].period = 0;
	a->objects[i].frequency = 0;
}

static void	init_objects(t_info *a)
{
	int i;

	i = -1;
	while (++i < a->scene->amount_of_objects)
	{
		a->objects[i].type = TYPELESS;
		a->objects[i].material = NONE;
		a->objects[i].albedo_n = -1;
		a->objects[i].tex_scale = 1;
		a->objects[i].emission = i_3(0, 0, 0);
		a->objects[i].dir = i_3(0, 0, 0);
		a->objects[i].point1 = i_3(0, 0, 0);
		a->objects[i].point2 = i_3(0, 0, 0);
		a->objects[i].point3 = i_3(0, 0, 0);
		a->objects[i].n = i_3(0, 0, 0);
		a->objects[i].edge0 = i_3(0, 0, 0);
		a->objects[i].edge1 = i_3(0, 0, 0);
		a->objects[i].edge2 = i_3(0, 0, 0);
		a->objects[i].color = i_3(0, 0, 0);
		a->objects[i].absorption = i_3(0, 0, 0);
		a->objects[i].upsilon = i_3(0, 0, 0);
		a->objects[i].radius = 1.0f;
		init_objects_(a, i);
	}
}

void		object_parsing(t_info *a, t_json_scene *js)
{
	cl_int	i;

	init_objects(a);
	i = -1;
	while (++i < a->scene->amount_of_objects)
	{
		js->object = cJSON_GetArrayItem(js->objects, i);
		js->type = cJSON_GetObjectItemCaseSensitive(js->object, "type");
		if (!cJSON_IsString(js->type))
		{
			object_error(a, i, "invalid type");
			continue ;
		}
		get_object_type(a, i, js->type->valuestring);
		parse_material(a, i, js);
		goto_parsing(a, i, js);
	}
}
