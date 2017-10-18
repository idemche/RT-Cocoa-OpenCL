/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 19:24:23 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/19 00:43:46 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		calculate_primary_rays(t_cl *cl, size_t global_work_size,
												size_t local_work_size,
												t_info *a)
{
	if (clSetKernelArg(cl->kernel_primary_rays, 4, sizeof(cl_int),
								(void *)(a->current_sample)) != CL_SUCCESS)
		ft_error("OpenCL error: Kernel set arg 4, curr_sample");
	if (clEnqueueNDRangeKernel(cl->queue, cl->kernel_primary_rays, 1, 0,
		(void *)&(global_work_size), (void *)&(local_work_size), 0, NULL,
														NULL) != CL_SUCCESS)
		ft_error("OpenCL error: Enqueue Range kernel_primary_rays");
	clFinish(cl->queue);
}

static void		no_light_calculation(t_cl *cl, size_t global_work_size,
												size_t local_work_size)
{
	if (clEnqueueNDRangeKernel(cl->queue, cl->kernel_intersections, 1, 0,
		(void *)&(global_work_size), (void *)&(local_work_size), 0, NULL,
														NULL) != CL_SUCCESS)
		ft_error("OpenCL error: Enqueue Range kernel_intersections");
	clFinish(cl->queue);
	if (clEnqueueNDRangeKernel(cl->queue, cl->kernel_textures, 1, 0,
		(void *)&(global_work_size), (void *)&(local_work_size), 0, NULL,
														NULL) != CL_SUCCESS)
		ft_error("OpenCL error: Enqueue Range kernel_textures");
	clFinish(cl->queue);
	if (clEnqueueNDRangeKernel(cl->queue, cl->kernel_trace, 1, 0,
		(void *)&(global_work_size), (void *)&(local_work_size), 0, NULL,
														NULL) != CL_SUCCESS)
		ft_error("OpenCL error: Enqueue Range kernel_trace");
	clFinish(cl->queue);
}

static void		main_loop(t_cl *cl, size_t global_work_size,
									size_t local_work_size,
										int depth)
{
	while (++depth < 6)
	{
		if (clEnqueueNDRangeKernel(cl->queue, cl->kernel_intersections, 1, 0,
			(void *)&(global_work_size), (void *)&(local_work_size), 0, NULL,
														NULL) != CL_SUCCESS)
			ft_error("OpenCL error: Enqueue Range kernel_intersections");
		clFinish(cl->queue);
		if (clEnqueueNDRangeKernel(cl->queue, cl->kernel_textures, 1, 0,
			(void *)&(global_work_size), (void *)&(local_work_size), 0, NULL,
														NULL) != CL_SUCCESS)
			ft_error("OpenCL error: Enqueue Range kernel_textures");
		clFinish(cl->queue);
		if (clEnqueueNDRangeKernel(cl->queue, cl->kernel_radiance, 1, 0,
			(void *)&(global_work_size), (void *)&(local_work_size), 0, NULL,
														NULL) != CL_SUCCESS)
			ft_error("OpenCL error: Enqueue Range kernel_radiance");
		clFinish(cl->queue);
		if (clEnqueueNDRangeKernel(cl->queue, cl->kernel_trace, 1, 0,
			(void *)&(global_work_size), (void *)&(local_work_size), 0, NULL,
														NULL) != CL_SUCCESS)
			ft_error("OpenCL error: Enqueue Range kernel_trace");
		clFinish(cl->queue);
	}
}

void			render_scene(t_info *a, t_cl *cl, int npixels)
{
	size_t global_work_size;
	size_t local_work_size;

	global_work_size = npixels;
	local_work_size = 64;
	calculate_primary_rays(cl, global_work_size, local_work_size, a);
	if (a->scene->light_on == 0)
		no_light_calculation(cl, global_work_size, local_work_size);
	else
		main_loop(cl, global_work_size, local_work_size, -1);
	if (clSetKernelArg(cl->kernel_write_image, 4, sizeof(cl_int),
							(void *)a->current_sample) != CL_SUCCESS)
		ft_error("OpenCL error: Kernel set arg 4, curr_sample");
	if (clEnqueueNDRangeKernel(cl->queue, cl->kernel_write_image, 1, 0,
		(void *)&(global_work_size), (void *)&(local_work_size), 0, NULL,
														NULL) != CL_SUCCESS)
		ft_error("OpenCL error: Enqueue Range kernel_write_image");
	clFinish(cl->queue);
	(*a->current_sample)++;
}
