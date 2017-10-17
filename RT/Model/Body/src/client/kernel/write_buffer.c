/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 19:24:23 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/16 16:00:56 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	write_buffers__(t_info *a, t_cl *cl)
{
	if (a->scene->amount_of_albedo_textures)
	{
		if (W_(cl->queue, cl->mem_albedo_textures, 2048 * 2048 * sizeof(VEC3) *
			a->scene->amount_of_albedo_textures, a->albedo_textures) != CL_OK)
			ft_error("Error: enqueue Write Buffer, albedo_textures");
		if (W_(cl->queue, cl->mem_normal_textures, 2048 * 2048 * sizeof(VEC3) *
			a->scene->amount_of_albedo_textures, a->normal_textures) != CL_OK)
			ft_error("OpenCL error: Enqueue Write Buffer, normal_textures");
	}
	if (a->scene->n_negative_obj)
	{
		if (W_(cl->queue, cl->mem_negative_objects, sizeof(t_object),
												a->negative_objects) != CL_OK)
			ft_error("OpenCL error: Enqueue Write Buffer, negative objects");
	}
}

static void	write_buffers_(t_info *a, t_cl *cl, int npixels)
{
	int i;

	a->seeds = (unsigned int *)malloc(sizeof(unsigned int) * npixels * 2);
	i = -1;
	while (++i < npixels * 2)
	{
		a->seeds[i] = rand();
		if (a->seeds[i] < 2)
			a->seeds[i] = 2;
	}
	if (W_(cl->queue, cl->mem_seed, sizeof(unsigned int) * npixels * 2,
		a->seeds) != CL_OK)
		ft_error("Failed to write the OpenCL seeds buffer");
	if (a->scene->amount_of_spotlights)
	{
		if (W_(cl->queue, cl->mem_lights, sizeof(t_spotlight) *
			a->scene->amount_of_spotlights, a->spotlights) != CL_OK)
			ft_error("OpenCL error: Enqueue Write Buffer, spotlights");
	}
}

void		write_buffers(t_info *a, t_cl *cl, int npixels)
{
	if (W_(cl->queue, cl->mem_scene, sizeof(t_scene), a->scene) != CL_OK)
		ft_error("OpenCL error: Enqueue Write Buffer, scene");
	if (W_(cl->queue, cl->mem_camera, sizeof(t_camera), a->camera) != CL_OK)
		ft_error("OpenCL error: Enqueue Write Buffer, camera");
	if (W_(cl->queue, cl->mem_perlin, sizeof(cl_float) * 800 * 800,
		a->perlin.values) != CL_OK)
		ft_error("OpenCL error: Enqueue Write Buffer, perlin");
	if (a->scene->env_map)
	{
		if (W_(cl->queue, cl->mem_env_map, sizeof(cl_float3)
			* a->scene->env_map_h * a->scene->env_map_w, a->environment_map)
			!= CL_OK)
			ft_error("OpenCL error: Enqueue Write Buffer, environment_map");
		free(a->environment_map);
	}
	if (W_(cl->queue, cl->mem_objects, sizeof(t_object) *
						a->scene->amount_of_objects, a->objects) != CL_OK)
		ft_error("OpenCL error: Enqueue Write Buffer, objects");
	write_buffers_(a, cl, npixels);
	write_buffers__(a, cl);
}
