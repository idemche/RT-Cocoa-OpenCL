/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reinit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 20:49:34 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/18 01:33:32 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	*thread_reinit(void *data)
{
	t_thread	*t;
	t_client	i;
	char		response[256];

	t = (t_thread*)data;
	send(t->clnt_socket, "reinit", 6, 0x2000);
	recv(t->clnt_socket, response, 256, 0);
	i.id = t->id;
	i.json_len = t->a->json_len;
	i.max_peers = t->server->max_peers;
	i.line_size = t->server->line_size;
	i.spp_per_call = t->a->spp_per_call;
	i.width = t->a->scene->image_width;
	i.height = t->a->scene->image_height;
	ft_putstr("Sending init info to client #\n");
	ft_putnbr(t->id);
	ft_putchar('\n');
	send(t->clnt_socket, &i, sizeof(t_client), 0x2000);
	ft_putstr("Sending json_file\n");
	send_to_socket(t->clnt_socket, (void*)t->a->json_file, t->a->json_len);
	t->clnt_socket = t->clnt_socket;
	recv(t->clnt_socket, response, 256, 0);
	send(t->clnt_socket, &i, sizeof(t_client), 0x2000);
	recv(t->clnt_socket, response, 256, 0);
	return (NULL);
}

void		update_threads(t_info *a)
{
	int		i;

	i = -1;
	while (++i < a->server.max_peers)
	{
		free(a->threads[i].data);
		a->threads[i].data = (t_uch*)malloc(a->server.line_size * sizeof(int));
		pthread_create(&(a->threads[i].thread), NULL, thread_reinit,
			&(a->threads[i]));
	}
	i = -1;
	while (++i < a->server.max_peers)
		pthread_join(a->threads[i].thread, NULL);
}

void		reinit_server(t_info *a)
{
	int		old_max_peers;

	old_max_peers = a->server.max_peers;
	a->update_map = 0;
	free(a->scene);
	free(a->current_sample);
	free(a->camera);
	a->json_len = get_file(a->scenes[a->num_scene], &a->json_file);
	if (a->json_len == 0)
	{
		exit_call(a);
		close(a->server.socket);
		exit(1);
	}
	init_server(a);
	a->server.max_peers = old_max_peers;
	a->server.line_size = a->server.image_size / old_max_peers;
	update_threads(a);
}
