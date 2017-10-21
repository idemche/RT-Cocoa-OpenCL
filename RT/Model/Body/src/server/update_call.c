/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_call.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 20:49:34 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/20 00:45:04 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	send_scene(t_thread *t)
{
	char		response[256];

	send(t->clnt_socket, "scene", 5, 0x2000);
	bzero((void*)&response, 256);
	recv(t->clnt_socket, response, 256, 0);
	if (!ft_strncmp(response, "sce", 3))
	{
		send(t->clnt_socket, t->a->scene, sizeof(t_scene), 0x2000);
		bzero((void*)&response, 256);
		recv(t->clnt_socket, response, 256, 0);
	}
}

static void	*thread_camera_update(void *thread_)
{
	t_thread	*thread;
	char		response[256];

	thread = (t_thread*)thread_;
	send(thread->clnt_socket, "update", 6, 0x2000);
	bzero((void*)&response, 256);
	recv(thread->clnt_socket, response, 256, 0);
	if (!ft_strncmp(response, "ok", 2))
		send_camera(thread);
	return (NULL);
}

static void	*thread_scene_update(void *thread_)
{
	t_thread	*thread;
	char		response[256];

	thread = (t_thread*)thread_;
	send(thread->clnt_socket, "update", 6, 0x2000);
	bzero((void*)&response, 256);
	recv(thread->clnt_socket, response, 256, 0);
	if (!ft_strncmp(response, "ok", 2))
		send_scene(thread);
	return (NULL);
}

void		update_camera_call(t_info *a)
{
	int		i;

	i = -1;
	while (++i < a->server.max_peers)
	{
		pthread_create(&(a->threads[i].thread), NULL, thread_camera_update,
			&(a->threads[i]));
	}
	i = -1;
	while (++i < a->server.max_peers)
		pthread_join(a->threads[i].thread, NULL);
	a->update_camera = 0;
	a->update_scene = 0;
}

void		update_scene_call(t_info *a)
{
	int		i;

	i = -1;
	while (++i < a->server.max_peers)
	{
		pthread_create(&(a->threads[i].thread), NULL, thread_scene_update,
			&(a->threads[i]));
	}
	i = -1;
	while (++i < a->server.max_peers)
		pthread_join(a->threads[i].thread, NULL);
	a->update_scene = 0;
}
