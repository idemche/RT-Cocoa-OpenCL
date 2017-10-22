/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:44:38 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/20 01:04:26 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

typedef struct	s_object
{
	VEC3		emission;
	VEC3		dir;
	VEC3		point1;
	VEC3		point2;
	VEC3		point3;
	VEC3		n;
	VEC3		edge0;
	VEC3		edge1;
	VEC3		edge2;
	VEC3		color;
	VEC3		absorption;
	VEC3		upsilon;
	VEC3		a;
	VEC3		b;
	VEC3		c;
	cl_float	tex_scale;
	cl_float	radius;
	cl_float	radius2;
	cl_float	bot;
	cl_float	top;
	cl_float	k;
	cl_float	c2;
	cl_float	glossiness;
	cl_float	kd;
	cl_float	refr_index;
	cl_float	tex_shift;
	cl_float	dummy1;
	cl_int		period;
	cl_int		frequency;
	cl_int		type;
	cl_int		material;
	cl_int		albedo_n;
	cl_int		dummy2;
	cl_int		dummy3;
	cl_int		dummy4;
}				t_object;

typedef struct	s_camera
{
	VEC3		pos;
	VEC3		dir;
	VEC3		right;
	VEC3		up;
	cl_float	fov;
	cl_float	aspectratio;
	cl_float	angle;
	cl_float	inv_width;
	cl_float	inv_height;
	cl_float	aperture;
	cl_float	focal_length;
	cl_float	t;
}				t_camera;

typedef struct	s_light
{
	VEC3		pos;
	VEC3		dir;
	VEC3		emission;
	VEC3		u;
	VEC3		v;
	VEC3		w;
	cl_float	alpha;
	cl_float	radius;
}				t_spotlight;

typedef struct	s_scene
{
	cl_float3	ambient;
	cl_float3	parallel_dir;
	cl_float3	parallel_emis;
	cl_int		image_width;
	cl_int		image_height;
	cl_int		amount_of_objects;
	cl_int		amount_of_spotlights;
	cl_int		amount_of_albedo_textures;
	cl_int		n_negative_obj;
	cl_int		env_map_w;
	cl_int		env_map_h;
	cl_float	max_distance;
	cl_float	gamma;
	cl_char		light_on;
	cl_char		parallel_light;
	cl_char		indirect_light;
	cl_char		spotlight;
	cl_char		v_eff;
	cl_char		amount_of_nodes;
	cl_char		node_id;
	cl_char		c_mode;
	cl_char		env_map;
	cl_char		radiance_env_map;
	cl_char		tone_mapper;
	cl_char		dummy[9];
}				t_scene;

void			render_scene(t_info *a, t_cl *cl, int npixels);
void			get_prime_rays(t_info *a);
void			get_depth_map(t_info *a, size_t global_work_size,
											size_t local_work_size, t_cl *cl);

#endif
