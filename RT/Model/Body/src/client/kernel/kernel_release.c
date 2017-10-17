/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel_release.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 19:24:23 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/17 18:32:43 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	free_buffers_norm(t_cl *cl)
{
	clReleaseMemObject(cl->mem_depth);
	clReleaseMemObject(cl->mem_state);
	clReleaseMemObject(cl->mem_current_rays);
	clReleaseMemObject(cl->mem_intersections);
	clReleaseMemObject(cl->mem_pixel);
	clReleaseMemObject(cl->mem_scene);
	clReleaseMemObject(cl->mem_objects);
	clReleaseMemObject(cl->mem_camera);
	clReleaseMemObject(cl->mem_seed);
	clReleaseMemObject(cl->mem_colors);
	clReleaseMemObject(cl->mem_perlin);
	clReleaseMemObject(cl->mem_albedo_textures);
	clReleaseMemObject(cl->mem_normal_textures);
	clReleaseMemObject(cl->mem_lights);
	clReleaseMemObject(cl->mem_negative_objects);
	clReleaseMemObject(cl->mem_env_map);
}

void		free_buffers(t_cl *cl, t_info *a)
{
	free_buffers_norm(cl);
	clReleaseContext(cl->context);
	clReleaseProgram(cl->program);
	clReleaseCommandQueue(cl->queue);
	clReleaseKernel(cl->kernel_depth);
	clReleaseKernel(cl->kernel_radiance);
	clReleaseKernel(cl->kernel_intersections);
	clReleaseKernel(cl->kernel_primary_rays);
	clReleaseKernel(cl->kernel_trace);
	clReleaseKernel(cl->kernel_write_image);
	clReleaseKernel(cl->kernel_textures);
	free(a->perlin.values);
	free(a->objects);
	free(a->seeds);
	free(a->normal_textures);
	free(a->albedo_textures);
	if (a->scene->n_negative_obj)
		free(a->negative_objects);
	if (a->scene->amount_of_spotlights)
		free(a->spotlights);
}
