/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 19:24:23 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/16 15:54:04 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_cl		*thread_get(void)
{
	static t_cl thread;

	return (&thread);
}

static void	kek_norm(t_cl *cl)
{
	cl->mem_intersections = NULL;
	cl->mem_depth = NULL;
	cl->mem_negative_objects = NULL;
	cl->platform_id = NULL;
	cl->device_id = NULL;
	cl->context = NULL;
	cl->queue = NULL;
}

void		init_mem_variables(t_cl *cl)
{
	cl->program = NULL;
	cl->kernel_depth = NULL;
	cl->kernel_radiance = NULL;
	cl->kernel_intersections = NULL;
	cl->kernel_primary_rays = NULL;
	cl->kernel_trace = NULL;
	cl->kernel_write_image = NULL;
	cl->kernel_textures = NULL;
	cl->mem_current_rays = NULL;
	cl->mem_lights = NULL;
	cl->mem_pixel = NULL;
	cl->mem_objects = NULL;
	cl->mem_scene = NULL;
	cl->mem_camera = NULL;
	cl->mem_seed = NULL;
	cl->mem_state = NULL;
	cl->mem_colors = NULL;
	cl->mem_albedo_textures = NULL;
	cl->mem_normal_textures = NULL;
	cl->mem_perlin = NULL;
	kek_norm(cl);
}

void		opencl_error(const char *err, const void *p, size_t cb, void *u)
{
	(void)p;
	(void)cb;
	(void)u;
	fprintf(stderr, "%s\n", err);
}
