/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 20:49:34 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/19 00:43:44 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		send_line(t_info *a, t_cl *cl)
{
	char	buf[256];

	if (clEnqueueReadBuffer(cl->queue, cl->mem_pixel, CL_TRUE, 0,
		a->client.line_size * sizeof(cl_int), a->line_data, 0, NULL, NULL)
			!= CL_OK)
		ft_error("OpenCL error: Enqueue Read Buffer, pixel");
	send(a->server.socket, "prepare", 7, 0x2000);
	bzero((void*)&buf, 256);
	recv(a->server.socket, buf, 256, 0);
	if (ft_strncmp(buf, "ok", 2))
		ft_putstr("something went wrong: sending line\n");
	else
	{
		if (!send_to_socket(a->server.socket, (char*)a->line_data,
													a->client.line_size * 4))
			ft_putstr("Sending failed\n");
	}
}

static void		check_updates(t_info *a, t_cl *cl)
{
	if (a->update_camera)
	{
		if (clEnqueueWriteBuffer(cl->queue, cl->mem_camera, CL_TRUE, 0,
					sizeof(t_camera), a->camera, 0, NULL, NULL) != CL_SUCCESS)
			ft_error("OpenCL error: Enqueue Write Buffer, camera");
		if (clEnqueueWriteBuffer(cl->queue, cl->mem_scene, CL_TRUE, 0,
					sizeof(t_scene), a->scene, 0, NULL, NULL) != CL_SUCCESS)
			ft_error("OpenCL error: Enqueue Write Buffer, scene");
		get_depth_map(a, a->client.line_size, 64, cl);
		*(a->current_sample) = 0;
		a->update_camera = 0;
		free(a->depth_map);
	}
	if (a->update_scene)
	{
		a->update_scene = 0;
		if (clEnqueueWriteBuffer(cl->queue, cl->mem_scene, CL_TRUE, 0,
					sizeof(t_scene), a->scene, 0, NULL, NULL) != CL_SUCCESS)
			ft_error("OpenCL error: Enqueue Write Buffer, scene");
	}
}

void			client_render(t_info *a)
{
	int		i;
	t_cl	*cl;

	send(a->server.socket, "ok", 2, 0x2000);
	cl = thread_get();
	check_updates(a, cl);
	i = -1;
	while (++i < a->client.spp_per_call)
	{
		render_scene(a, cl, a->client.line_size);
		ft_putstr("\033[A\033[2K");
		rewind(stdout);
		ft_putstr("spp: ");
		ft_putnbr(*(a->current_sample));
		ft_putchar('\n');
	}
	send_line(a, cl);
}
