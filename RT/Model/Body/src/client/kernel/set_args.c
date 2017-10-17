/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 19:24:23 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/10 17:45:10 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		set_args_kernel_intersections(t_cl *cl)
{
	if (SET_ARG(cl->kernel_intersections, 0, cl->mem_intersections) != CL_OK)
		ft_error("OpenCL error: kernel_intersections set arg 0, intersection");
	if (SET_ARG(cl->kernel_intersections, 1, cl->mem_scene) != CL_OK)
		ft_error("OpenCL error: kernel_intersections set arg 1, mem_scene");
	if (SET_ARG(cl->kernel_intersections, 2, cl->mem_objects) != CL_OK)
		ft_error("OpenCL error: kernel_intersections set arg 2, mem_objects");
	if (SET_ARG(cl->kernel_intersections, 3, cl->mem_current_rays) != CL_OK)
		ft_error("OpenCL error: kernel_intersections set arg 3, mem_current");
	if (SET_ARG(cl->kernel_intersections, 4, cl->mem_lights) != CL_OK)
		ft_error("OpenCL error: kernel_intersections set arg 5, mem_lights");
	if (SET_ARG(cl->kernel_intersections, 5, cl->mem_seed) != CL_OK)
		ft_error("OpenCL error: kernel_intersections set arg 5, mem_seeds");
	if (SET_ARG(cl->kernel_intersections, 6, cl->mem_negative_objects)
																	!= CL_OK)
		ft_error("OpenCL error: kernel_negative set arg 6, negative_obj");
	if (SET_ARG(cl->kernel_intersections, 7, cl->mem_state) != CL_OK)
		ft_error("OpenCL error: kernel_negative set arg 7, negative_obj");
	if (SET_ARG(cl->kernel_intersections, 8, cl->mem_env_map) != CL_OK)
		ft_error("OpenCL error: kernel_intersections set arg 8, env_map");
}

static void		set_args_kernel_primary_rays(t_cl *cl)
{
	if (SET_ARG(cl->kernel_primary_rays, 0, cl->mem_current_rays) != CL_OK)
		ft_error("OpenCL error: kernel_primary_rays set arg 0, mem_current_r");
	if (SET_ARG(cl->kernel_primary_rays, 1, cl->mem_scene) != CL_OK)
		ft_error("OpenCL error: kernel_primary_rays set arg 1, mem_scene");
	if (SET_ARG(cl->kernel_primary_rays, 2, cl->mem_camera) != CL_OK)
		ft_error("OpenCL error: kernel_primary_rays set arg 2, mem_camera");
	if (SET_ARG(cl->kernel_primary_rays, 3, cl->mem_seed) != CL_OK)
		ft_error("OpenCL error: kernel_primary_rays set arg 3, mem_seeds");
	if (SET_ARG(cl->kernel_primary_rays, 5, cl->mem_state) != CL_OK)
		ft_error("OpenCL error: kernel_primary_rays set arg 5, mem_state");
	if (SET_ARG(cl->kernel_write_image, 0, cl->mem_pixel) != CL_OK)
		ft_error("OpenCL error: kernel_write_image set arg 0, pixels");
	if (SET_ARG(cl->kernel_write_image, 2, cl->mem_scene) != CL_OK)
		ft_error("OpenCL error: kernel_write_image set arg 2, mem_scene");
	if (SET_ARG(cl->kernel_write_image, 3, cl->mem_colors) != CL_OK)
		ft_error("OpenCL error: kernel_write_image set arg 3, mem_colors");
	if (SET_ARG(cl->kernel_write_image, 5, cl->mem_depth) != CL_OK)
		ft_error("OpenCL error: kernel_write_image set arg 5, depth_map");
}

static void		set_args_kernel_textures(t_cl *cl)
{
	if (SET_ARG(cl->kernel_textures, 0, cl->mem_intersections) != CL_OK)
		ft_error("OpenCL error: kernel_textures set arg 0, intersections");
	if (SET_ARG(cl->kernel_textures, 1, cl->mem_scene) != CL_OK)
		ft_error("OpenCL error: kernel_textures set arg 1, mem_scene");
	if (SET_ARG(cl->kernel_textures, 2, cl->mem_objects) != CL_OK)
		ft_error("OpenCL error: kernel_textures set arg 2, mem_objects");
	if (SET_ARG(cl->kernel_textures, 3, cl->mem_albedo_textures) != CL_OK)
		ft_error("OpenCL error: kernel_textures set arg 3, mem_albedo_textur");
	if (SET_ARG(cl->kernel_textures, 4, cl->mem_normal_textures) != CL_OK)
		ft_error("OpenCL error: kernel_textures set arg 4, mem_normal_textur");
	if (SET_ARG(cl->kernel_textures, 5, cl->mem_perlin) != CL_OK)
		ft_error("OpenCL error: kernel_textures set arg 5, mem_perlin");
	if (SET_ARG(cl->kernel_depth, 0, cl->mem_depth) != CL_OK)
		ft_error("OpenCL error: kernel_depth set arg 0, depth_map");
	if (SET_ARG(cl->kernel_depth, 1, cl->mem_current_rays) != CL_OK)
		ft_error("OpenCL error: kernel_depth set arg 1, mem_current_rays");
	if (SET_ARG(cl->kernel_depth, 2, cl->mem_scene) != CL_OK)
		ft_error("OpenCL error: kernel_depth set arg 2, mem_scene");
	if (SET_ARG(cl->kernel_depth, 3, cl->mem_objects) != CL_OK)
		ft_error("OpenCL error: kernel_depth set arg 3, mem_objects");
	if (SET_ARG(cl->kernel_depth, 4, cl->mem_negative_objects) != CL_OK)
		ft_error("OpenCL error: kernel_depth set arg 4, mem_negative_objects");
}

static void		set_args_kernel_radiance(t_cl *cl)
{
	if (SET_ARG(cl->kernel_radiance, 0, cl->mem_intersections) != CL_OK)
		ft_error("OpenCL error: kernel_radiance set arg 0, intersections");
	if (SET_ARG(cl->kernel_radiance, 1, cl->mem_scene) != CL_OK)
		ft_error("OpenCL error: kernel_radiance set arg 1, mem_scene");
	if (SET_ARG(cl->kernel_radiance, 2, cl->mem_objects) != CL_OK)
		ft_error("OpenCL error: kernel_radiance set arg 2, mem_objects");
	if (SET_ARG(cl->kernel_radiance, 3, cl->mem_lights) != CL_OK)
		ft_error("OpenCL error: kernel_radiance set arg 3, mem_lights");
	if (SET_ARG(cl->kernel_radiance, 4, cl->mem_seed) != CL_OK)
		ft_error("OpenCL error: kernel_radiance set arg 4, mem_seeds");
	if (SET_ARG(cl->kernel_radiance, 5, cl->mem_albedo_textures) != CL_OK)
		ft_error("OpenCL error: kernel_textures set arg 5, mem_albedo_textur");
	if (SET_ARG(cl->kernel_radiance, 6, cl->mem_perlin) != CL_OK)
		ft_error("OpenCL error: kernel_textures set arg 6, mem_perlin");
	if (SET_ARG(cl->kernel_radiance, 7, cl->mem_negative_objects) != CL_OK)
		ft_error("OpenCL error: kernel_textures set arg 7, mem_negative_obje");
	if (SET_ARG(cl->kernel_radiance, 8, cl->mem_env_map) != CL_OK)
		ft_error("OpenCL error: kernel_radiance set arg 8, env_map");
}

void			set_args(t_cl *cl)
{
	set_args_kernel_primary_rays(cl);
	set_args_kernel_textures(cl);
	set_args_kernel_radiance(cl);
	set_args_kernel_intersections(cl);
	if (SET_ARG(cl->kernel_write_image, 1, cl->mem_state) != CL_OK)
		ft_error("OpenCL error: kernel_write_image set arg 0, mem_state");
	if (SET_ARG(cl->kernel_trace, 0, cl->mem_state) != CL_OK)
		ft_error("OpenCL error: kernel_trace set arg 0, mem_state");
	if (SET_ARG(cl->kernel_trace, 1, cl->mem_intersections) != CL_OK)
		ft_error("OpenCL error: kernel_trace set arg 1, intersections");
	if (SET_ARG(cl->kernel_trace, 2, cl->mem_objects) != CL_OK)
		ft_error("OpenCL error: kernel_trace set arg 2, mem_objects");
	if (SET_ARG(cl->kernel_trace, 3, cl->mem_scene) != CL_OK)
		ft_error("OpenCL error: kernel_trace set arg 3, mem_scene");
	if (SET_ARG(cl->kernel_trace, 4, cl->mem_current_rays) != CL_OK)
		ft_error("OpenCL error: kernel_trace set arg 4, mem_current_rays");
	if (SET_ARG(cl->kernel_trace, 5, cl->mem_seed) != CL_OK)
		ft_error("OpenCL error: kernel_trace set arg 5, mem_seeds");
}
