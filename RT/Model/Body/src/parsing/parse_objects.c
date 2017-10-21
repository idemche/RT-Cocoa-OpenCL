/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:53:16 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/20 14:24:43 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_parse_ft const g_parse_object[] = {sphere_parsing, plane_parsing,
	cylinder_parsing, cone_parsing, paraboloid_parsing, torus_parsing,
	disk_parsing, triangle_parsing, cube_parsing, box_parsing, bocal_parsing,
	mob_parsing, elipsoid_parsing, dna_parsing, heart_parsing,
	cubehole_parsing, tetrahedron_parsing, star_parsing, octahedron_parsing,
	cubohedron_parsing, ring_parsing, typeless_parsing};

static char *g_types[] = {"SPHERE", "PLANE", "CYLINDER", "CONE",
	"PARABOLOID", "TORUS", "DISK", "TRIANGLE", "CUBE", "BOX", "BOCAL",
	"MOEBIUS", "ELIPSOID", "DNA", "HEART", "CUBEHOLE", "TETRAHEDRON",
	"STELLATED OCTAHEDRON", "OCTAHEDRON", "CUBOHEDRON", "RING"};

void		typeless_parsing(t_info *a, int i, t_object *o, t_json_scene *j)
{
	o->material = NONE;
	j->object = NULL;
	object_error(a, i, "invalid object type");
}

void		get_object_type(t_info *a, cl_int i, char *type_str)
{
	t_typename	type;

	type = SPHERE - 1;
	while (++type < TYPELESS)
	{
		if (!ft_strcmp(type_str, g_types[type]))
		{
			a->objects[i].type = type;
			break ;
		}
	}
	a->objects[i].type = type;
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
		g_parse_object[a->objects[i].type](a, i, &(a->objects[i]), js);
	}
}
