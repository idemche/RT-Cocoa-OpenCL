/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 19:24:23 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/19 00:43:41 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		init_kernel__(t_cl *cl, int err)
{
	cl->kernel_radiance = clCreateKernel(cl->program,
														"get_radiance", &err);
	if (err != CL_SUCCESS)
		ft_error("OpenCL error: kernel_radiance");
	cl->kernel_depth = clCreateKernel(cl->program,
												"generate_depth_map", &err);
	if (err != CL_SUCCESS)
		ft_error("OpenCL error: kernel_depth");
	cl->kernel_write_image = clCreateKernel(cl->program,
														"get_image", &err);
	if (err != CL_SUCCESS)
		ft_error("OpenCL error: kernel_write_image");
	cl->kernel_primary_rays = clCreateKernel(cl->program,
													"compute_prime_ray", &err);
	if (err != CL_SUCCESS)
		ft_error("OpenCL error: kernel_primary_rays");
	cl->kernel_trace = clCreateKernel(cl->program, "do_trace", &err);
	if (err != CL_SUCCESS)
		ft_error("OpenCL error: kernel_trace");
	cl->kernel_textures = clCreateKernel(cl->program, "get_texturing",
																		&err);
	if (err != CL_SUCCESS)
		ft_error("OpenCL error: kernel_textures");
}

static void		init_kernel_(t_cl *cl, int err, char *src_file)
{
	size_t size;

	size = get_file("kernels.cl", &src_file);
	if (size == 0)
		exit(-2);
	cl->program = clCreateProgramWithSource(cl->context,
					1, (const char **)&src_file, (const size_t *)&size, &err);
	free(src_file);
	if (err != CL_SUCCESS)
		ft_error("OpenCL error: program source: intersections");
	if ((err = clBuildProgram(cl->program, 1, &(cl->device_id),
			"-cl-fast-relaxed-math -DMAC -cl-single-precision-constant",
													NULL, NULL)) != CL_SUCCESS)
		ft_error("OpenCL error: build program intersections");
	cl->kernel_intersections = clCreateKernel(cl->program,
												"compute_intersection", &err);
	if (err != CL_SUCCESS)
		ft_error("OpenCL error: kernel_intersections");
	init_kernel__(cl, err);
}

static void		init_kernel(t_cl *cl)
{
	int			err;
	char		*source_file;
	size_t		size;

	source_file = NULL;
	size = 0;
	err = clGetPlatformIDs(1, &(cl->platform_id), &(cl->platform_count));
	if (err != CL_SUCCESS)
		ft_error("OpenCL error: platform_id");
	err = clGetDeviceIDs(cl->platform_id, CL_DEVICE_TYPE_GPU, 1,
										&(cl->device_id), &(cl->device_count));
	if (err != CL_SUCCESS)
		ft_error("OpenCL error: device_id");
	cl->context = clCreateContext(NULL, 1, &(cl->device_id), opencl_error,
																NULL, &err);
	if (err != CL_SUCCESS)
		ft_error("OpenCL error: context");
	cl->queue = clCreateCommandQueue(cl->context, cl->device_id, 0, &err);
	if (err != CL_SUCCESS)
		ft_error("OpenCL error: queue");
	init_kernel_(cl, err, source_file);
}

void			init_opencl(t_info *a)
{
	t_cl		*cl;

	cl = thread_get();
	init_mem_variables(cl);
	init_kernel(cl);
	init_buffers(a, cl, a->client.line_size);
}
