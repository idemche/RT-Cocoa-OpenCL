/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:44:38 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/19 19:28:44 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "rt.h"

# define EPS 1e-4
# define INF 1e20f
# define PERLIN -3
# define NORMAL -2
# define CHECKERBOARD -4
# define TRUE_CHECKER -5

typedef enum e_typename			t_typename;
typedef enum e_material			t_material;
typedef enum e_tone_mapper		t_tone_mapper;
typedef struct s_texture		t_texture;
typedef struct s_tmp_tex		t_tmp_tex;
typedef struct s_sequence		t_sequence;

enum		e_typename
{
	SPHERE, PLANE, CYLINDER, CONE, PARABOLOID, TORUS, DISK, TRIANGLE, CUBE,
	BOX, BOCAL, MOEBIUS, ELIPSOID, DNA, HEART, CUBEHOLE, TETRAHEDRON, STAR,
	OCTAHEDRON, CUBOHEDRON, RING, TYPELESS
};

enum		e_material
{
	DIFF, SPEC, REFR, GLOSSY, GLOSSY_REFR, TRANSPARENT, NONE
};

enum		e_tone_mapper
{
	STANDARD, UNCHARTED, STRONG
};

typedef	void	(*t_parse_ft)(t_info *a, int i, t_object *o, t_json_scene *j);

struct		s_texture
{
	t_uch		*data;
};

struct		s_tmp_tex
{
	t_uch		*tmp_rgba;
	int			y;
	int			x;
	t_uint		width;
	t_uint		height;
	t_uch		*rgba_albedo;
	t_uch		*rgba_normal;
	char		*tex_path_albedo;
	char		*tex_path_normal;
};

struct		s_sequence
{
	t_quaternion	q;
	cl_float3		axis;
	cl_float3		look_at;
	double			t;
	int				fps;
	int				is_on;
	int				frame_n;
	int				frame_max;
	char			*buf;
};

void		parse_scene(t_info *a, char *json_file);
void		light_parsing(t_info *a, t_json_scene *js);
void		cam_parsing(t_info *a, cJSON *root);
void		object_parsing(t_info *a, t_json_scene *js);
void		get_object_type(t_info *a, cl_int i, char *type);
void		octahedron_parsing(t_info *a, int i, t_object *o, t_json_scene *j);
void		cubohedron_parsing(t_info *a, int i, t_object *o, t_json_scene *j);
void		typeless_parsing(t_info *a, int i, t_object *o, t_json_scene *j);
void		star_parsing(t_info *a, int i, t_object *o, t_json_scene *j);
void		plane_parsing(t_info *a, int i, t_object *o, t_json_scene *j);
void		box_parsing(t_info *a, int i, t_object *o, t_json_scene *j);
void		sphere_parsing(t_info *a, int i, t_object *o, t_json_scene *j);
void		cone_parsing(t_info *a, int i, t_object *o, t_json_scene *j);
void		cylinder_parsing(t_info *a, int i, t_object *o, t_json_scene *j);
void		mob_parsing(t_info *a, int i, t_object *o, t_json_scene *j);
void		paraboloid_parsing(t_info *a, int i, t_object *o, t_json_scene *j);
void		disk_parsing(t_info *a, int i, t_object *o, t_json_scene *j);
void		triangle_parsing(t_info *a, int i, t_object *o, t_json_scene *j);
void		torus_parsing(t_info *a, int i, t_object *o, t_json_scene *j);
void		cube_parsing(t_info *a, int i, t_object *o, t_json_scene *j);
void		dna_parsing(t_info *a, int i, t_object *o, t_json_scene *j);
void		bocal_parsing(t_info *a, int i, t_object *o, t_json_scene *j);
void		elipsoid_parsing(t_info *a, int i, t_object *o, t_json_scene *j);
void		heart_parsing(t_info *a, int i, t_object *o, t_json_scene *j);
void		cubehole_parsing(t_info *a, int i, t_object *o, t_json_scene *j);
void		ring_parsing(t_info *a, int i, t_object *o, t_json_scene *js);
void		tetrahedron_parsing(t_info *a, int i, t_object *o,
															t_json_scene *j);
void		parse_color(t_info *a, int i, VEC3 *result, cJSON *color);
int			parse_point(VEC3 *result, cJSON *point);
void		parse_material(t_info *a, int i, t_json_scene *js);
void		parse_emission(t_info *a, VEC3 *result, cJSON *color);
void		parse_environment_map(t_info *a, t_json_scene *js);
void		parse_negative_object(t_info *a, t_json_scene *js);
void		sequence_parse(t_info *a, cJSON *root);
void		environment_parsing(t_info *a, t_json_scene *js);
void		restructurize_objects(t_info *a);
void		init_cam(t_info *a);
bool		check_vec3(VEC3 v);
int			parse_texture(t_info *a);
void		get_unique_texture_number(t_info *a);
void		check_unique_textures(t_info *a, int number);
void		write_textures(t_info *a, int i, int x, int y);
void		write_transform_matrix_to_object(t_object *object);
void		parse_texture_config(t_info *a, int i, t_json_scene *js,
														t_json_material *m);
void		get_object_info(t_json_object *o, t_json_scene *js);

#endif
