/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_call.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 20:49:34 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/16 14:42:22 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	recieve_line(t_thread *thread)
{
	char		response[256];

	ft_bzero((void*)&response, 256);
	recv(thread->clnt_socket, response, 256, 0);
	if (ft_strncmp(response, "prepare", 7))
		send(thread->clnt_socket, "fail", 4, 0x2000);
	else
	{
		send(thread->clnt_socket, "ok", 2, 0x2000);
		if (!recv_from_socket(thread->clnt_socket, thread->data,
									thread->server->line_size * sizeof(int)))
			ft_putstr("fail while recieving line\n");
	}
}

static void	*thread_render(void *thread_)
{
	t_thread	*thread;
	char		response[256];

	thread = (t_thread*)thread_;
	send(thread->clnt_socket, "render", 6, 0x2000);
	ft_bzero((void*)&response, 256);
	recv(thread->clnt_socket, response, 256, 0);
	if (!ft_strncmp(response, "max", 3))
		return (NULL);
	else if (!ft_strncmp(response, "ok", 2))
		recieve_line(thread);
	return (NULL);
}

void		render_call(t_info *a)
{
	int		i;

	i = -1;
	while (++i < a->server.max_peers)
	{
		pthread_create(&(a->threads[i].thread), NULL, thread_render,
			&(a->threads[i]));
	}
	i = -1;
	while (++i < a->server.max_peers)
		pthread_join(a->threads[i].thread, NULL);
}
