/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depth_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 19:24:23 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/17 11:52:55 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		write_depth_map(t_info *a, size_t global, size_t local,
																	t_cl *cl)
{
	if (clEnqueueNDRangeKernel(cl->queue, cl->kernel_depth, 1, 0,
		(void *)&(global), (void *)&(local), 0, NULL,
														NULL) != CL_SUCCESS)
		ft_error("OpenCL error: Enqueue Range kernel_depth");
	clFinish(cl->queue);
	a->depth_map = (cl_float*)malloc(sizeof(cl_float) * global);
	if (clEnqueueReadBuffer(cl->queue, cl->mem_depth, CL_TRUE, 0,
		global * sizeof(cl_float), a->depth_map, 0, NULL,
														NULL) != CL_SUCCESS)
		ft_error("OpenCL error: Enqueue Read Buffer, depth_map");
}

void			get_depth_map(t_info *a, size_t global, size_t local, t_cl *cl)
{
	float	min;
	float	max;
	int		i;

	write_depth_map(a, global, local, cl);
	min = INF;
	max = -INF;
	i = -1;
	while (++i < (int)global)
	{
		if (a->depth_map[i] < min)
			min = a->depth_map[i];
		if (a->depth_map[i] > max)
			max = a->depth_map[i];
	}
	i = -1;
	while (++i < (int)global)
		a->depth_map[i] = (a->depth_map[i] - min) / (max - min);
	a->scene->max_distance = max;
	if (clEnqueueWriteBuffer(cl->queue, cl->mem_depth, CL_TRUE, 0,
		sizeof(cl_float) * global, (void *)&(*a->depth_map), 0, NULL,
													NULL) != CL_SUCCESS)
		ft_error("Failed to write the OpenCL depth_map buffer");
}
