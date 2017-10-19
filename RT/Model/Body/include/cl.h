/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:44:38 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/19 19:24:02 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CL_H
# define CL_H

# include <OpenCL/OpenCL.h>
# include "rt.h"

# define CHECK(err, str) {if (err != CL_SUCCESS) ft_error(str);}
# define SET_ARG(k, n, m) (clSetKernelArg(k, n, sizeof(cl_mem), (void *)&(m)))
# define T CL_TRUE
# define CL_OK CL_SUCCESS
# define W_(q, m, s, o) (clEnqueueWriteBuffer(q, m, T, 0, s, o, 0, NULL, NULL))

typedef struct s_intersection	t_intersection;
typedef struct s_ray			t_ray;
typedef struct s_negative		t_negative;
typedef struct s_state			t_state;

struct			s_cl
{
	cl_platform_id		platform_id;
	cl_uint				platform_count;
	cl_device_id		device_id;
	cl_uint				device_count;
	cl_context			context;
	cl_command_queue	queue;
	cl_mem				mem_pixel;
	cl_mem				mem_scene;
	cl_mem				mem_camera;
	cl_mem				mem_lights;
	cl_mem				mem_objects;
	cl_mem				mem_state;
	cl_mem				mem_seed;
	cl_mem				mem_colors;
	cl_mem				mem_albedo_textures;
	cl_mem				mem_normal_textures;
	cl_mem				mem_perlin;
	cl_mem				mem_depth;
	cl_mem				mem_negative_objects;
	cl_mem				mem_primary_rays;
	cl_mem				mem_current_rays;
	cl_mem				mem_intersections;
	cl_mem				mem_env_map;
	cl_program			program;
	cl_kernel			kernel_trace;
	cl_kernel			kernel_depth;
	cl_kernel			kernel_textures;
	cl_kernel			kernel_radiance;
	cl_kernel			kernel_write_image;
	cl_kernel			kernel_intersections;
	cl_kernel			kernel_primary_rays;
};

struct			s_intersection
{
	cl_float3		hit_point;
	cl_float3		normal;
	cl_float3		radiance;
	cl_float3		u;
	cl_float3		v;
	cl_float3		color;
	cl_int			took_place;
};

struct			s_ray
{
	VEC3		d;
	VEC3		o;
	cl_float	t;
};

struct			s_negative
{
	cl_float3		hit_point;
	cl_float3		normal;
	cl_float2		range;
};

struct			s_state
{
	cl_float3		rad;
	cl_float3		path_capacity;
	cl_float3		current_absorption;
	cl_int			specular_bounce;
	cl_int			glossy_bounce;
	cl_int			through_transparent;
	cl_int			is_survive;
};

void			opencl_error(const char *e, const void *p, size_t cb, void *u);
void			init_opencl(t_info *a);
t_cl			*thread_get(void);
void			free_buffers(t_cl *cl, t_info *a);
void			init_buffers(t_info *a, t_cl *cl, int npixels);
void			write_buffers(t_info *a, t_cl *cl, int npixels);
void			init_mem_variables(t_cl *cl);
void			set_args(t_cl *cl);

#endif
