/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   peer_collector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 20:49:34 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/16 19:04:56 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		*thread_upd_info(void *t_)
{
	t_thread		*t;
	t_client		i;
	char			buf[256];

	t = (t_thread*)t_;
	i.id = t->id;
	i.json_len = t->json_len;
	i.max_peers = t->server->max_peers;
	i.line_size = t->server->line_size;
	i.spp_per_call = t->a->spp_per_call;
	i.width = t->a->scene->image_width;
	i.height = t->a->scene->image_height;
	send(t->clnt_socket, &i, sizeof(t_client), 0x2000);
	ft_bzero((void*)&buf, 256);
	recv(t->clnt_socket, buf, 256, 0);
	return (NULL);
}

static void		finalise_collecting(t_info *a, int i)
{
	a->server.max_peers = i;
	a->server.line_size = a->server.image_size / a->server.max_peers;
	if (a->scene->image_height % a->server.max_peers != 0)
		ft_error("Image height must be a multiple of maxpeers");
	i = -1;
	while (++i < a->server.max_peers)
	{
		a->threads[i].data = (t_uch*)malloc(a->server.line_size *
																sizeof(int));
		a->threads[i].server->max_peers = a->server.max_peers;
		a->threads[i].server->line_size = a->server.line_size;
		pthread_create(&(a->threads[i].thread), NULL, thread_upd_info,
			&(a->threads[i]));
	}
	i = -1;
	while (++i < a->server.max_peers)
		pthread_join(a->threads[i].thread, NULL);
}

static char		*catch_peer(t_info *a, int start_port, int i, t_server udp_serv)
{
	t_udp	udp;
	t_uint	clientlen;
	char	*buf;

	buf = (char*)malloc(BUFF_SIZE);
	clientlen = sizeof(udp.clientaddr);
	ft_bzero(buf, BUFF_SIZE);
	recvfrom(udp_serv.socket, buf, BUFF_SIZE, 0,
							(struct sockaddr *)&udp.clientaddr, &clientlen);
	gethostbyaddr((const char *)&udp.clientaddr.sin_addr.s_addr,
							sizeof(udp.clientaddr.sin_addr.s_addr), AF_INET);
	udp.hostaddrp = inet_ntoa(udp.clientaddr.sin_addr);
	printf("Server received datagram from %s: %s", udp.hostaddrp, buf);
	a->threads[i].server = create_tcp_server(a->server, start_port);
	sendto(udp_serv.socket, (void*)(&start_port), 4, 0,
							(struct sockaddr *)&udp.clientaddr, clientlen);
	accept_connection(&(a->threads[i]));
	return (buf);
}

void			collect_peers(t_info *a)
{
	int					start_port;
	int					i;
	char				*buf;
	t_server			udp_server;

	udp_server = create_udp_server(a);
	start_port = a->tcp_port;
	i = 0;
	while (i < 100)
	{
		buf = catch_peer(a, start_port, i, udp_server);
		i++;
		start_port++;
		if (!ft_strncmp(buf, "last", 4))
		{
			free(buf);
			break ;
		}
		free(buf);
	}
	finalise_collecting(a, i);
}
