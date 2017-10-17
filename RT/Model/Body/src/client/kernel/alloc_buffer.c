/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 19:24:23 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/17 19:57:30 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	alloc_buffers_(t_info *a, t_cl *cl, int **err)
{
	cl->mem_perlin = clCreateBuffer(cl->context, CL_MEM_READ_ONLY,
							sizeof(cl_float) * 800 * 800, NULL, &((*err)[10]));
	if (a->scene->amount_of_albedo_textures)
	{
		cl->mem_albedo_textures = clCreateBuffer(cl->context, CL_MEM_READ_ONLY,
		sizeof(VEC3) * 2048 * 2048 * a->scene->amount_of_albedo_textures, NULL,
		&((*err)[11]));
		cl->mem_normal_textures = clCreateBuffer(cl->context, CL_MEM_READ_ONLY,
			2048 * 2048 * sizeof(VEC3) * a->scene->amount_of_albedo_textures,
														NULL, &((*err)[12]));
	}
	else
	{
		cl->mem_albedo_textures = clCreateBuffer(cl->context, CL_MEM_READ_ONLY,
		sizeof(cl_float4), NULL, &((*err)[11]));
		cl->mem_normal_textures = clCreateBuffer(cl->context, CL_MEM_READ_ONLY,
		sizeof(cl_float4), NULL, &((*err)[12]));
	}
	if (a->scene->amount_of_spotlights)
		cl->mem_lights = clCreateBuffer(cl->context, CL_MEM_READ_ONLY,
		sizeof(t_spotlight) * a->scene->amount_of_spotlights, NULL,
																&((*err)[13]));
	else
		cl->mem_lights = clCreateBuffer(cl->context, CL_MEM_READ_ONLY,
		sizeof(cl_float4), NULL, &((*err)[13]));
}

static void	alloc_buffers__(t_info *a, t_cl *cl, int *err)
{
	int i;
	int res;

	if (a->scene->n_negative_obj)
		cl->mem_negative_objects = clCreateBuffer(cl->context,
			CL_MEM_READ_WRITE, sizeof(t_object) * a->scene->n_negative_obj,
															NULL, &err[14]);
	else
		cl->mem_negative_objects = clCreateBuffer(cl->context,
			CL_MEM_READ_WRITE, sizeof(cl_float4), NULL, &err[14]);
	if (a->scene->env_map)
		cl->mem_env_map = clCreateBuffer(cl->context,
			CL_MEM_READ_WRITE, sizeof(cl_float3) * a->scene->env_map_h *
										a->scene->env_map_w, NULL, &err[15]);
	else
		cl->mem_env_map = clCreateBuffer(cl->context,
			CL_MEM_READ_WRITE, sizeof(cl_float4), NULL, &err[15]);
	i = -1;
	res = 0;
	while (++i < 16)
		res |= err[i];
	if (res != CL_SUCCESS)
		ft_error("OpenCL error: buffer allocation");
	free(err);
}

static void	alloc_buffers(t_info *a, t_cl *cl, int npixels)
{
	int *err;

	err = (int*)malloc(sizeof(int) * 16);
	cl->mem_depth = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
								sizeof(cl_float) * npixels, NULL, &err[0]);
	cl->mem_state = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
								sizeof(t_state) * npixels, NULL, &err[1]);
	cl->mem_current_rays = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
								sizeof(t_ray) * npixels, NULL, &err[2]);
	cl->mem_intersections = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
							sizeof(t_intersection) * npixels, NULL, &err[3]);
	cl->mem_pixel = clCreateBuffer(cl->context, CL_MEM_WRITE_ONLY, npixels *
								sizeof(cl_int), NULL, &err[4]);
	cl->mem_scene = clCreateBuffer(cl->context, CL_MEM_READ_ONLY,
								sizeof(t_scene), NULL, &err[5]);
	cl->mem_objects = clCreateBuffer(cl->context, CL_MEM_READ_ONLY,
				sizeof(t_object) * a->scene->amount_of_objects, NULL, &err[6]);
	cl->mem_camera = clCreateBuffer(cl->context, CL_MEM_READ_ONLY,
								sizeof(t_camera), NULL, &err[7]);
	cl->mem_seed = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
							sizeof(unsigned int) * npixels * 2, NULL, &err[8]);
	cl->mem_colors = clCreateBuffer(cl->context, CL_MEM_READ_WRITE, npixels *
								sizeof(cl_float3), NULL, &err[9]);
	alloc_buffers_(a, cl, &err);
	alloc_buffers__(a, cl, err);
}

void		init_buffers(t_info *a, t_cl *cl, int npixels)
{
	alloc_buffers(a, cl, npixels);
	write_buffers(a, cl, npixels);
	set_args(cl);
}
