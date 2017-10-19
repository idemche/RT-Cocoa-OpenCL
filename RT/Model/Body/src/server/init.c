/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 20:49:34 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/19 15:50:55 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			init_threads(t_info *a, char *json_file, size_t json_len)
{
	int len;

	a->threads = (t_thread*)malloc(sizeof(t_thread) * 100);
	len = -1;
	while (++len < 100)
	{
		a->threads[len].a = a;
		a->threads[len].id = len;
		a->threads[len].json_len = json_len;
		a->threads[len].json_file = json_file;
	}
}

void			init_server_info(t_info *a, char *json_file)
{
	t_json_scene	js;

	a->scene_is_valid = 1;
	js.root = cJSON_Parse(json_file);
	environment_parsing(a, &js);
	a->scene->image_width = a->image_width;
	a->scene->image_height = a->image_height;
	a->server.image_size = a->scene->image_width * a->scene->image_height;
	sequence_parse(a, js.root);
	cam_parsing(a, js.root);
	cJSON_Delete(js.root);
}

t_server		create_udp_server(t_info *a)
{
	struct sockaddr_in	server;
	t_server			result;

	result.port = ft_atoi(a->port);
	result.socket = socket(AF_INET, SOCK_DGRAM, 0);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(result.port);
	le_error(bind(result.socket, (struct sockaddr*)&server, sizeof(server)));
	ft_putstr("Binded\n");
	listen(result.socket, 4);
	return (result);
}

t_server		*create_tcp_server(t_server o, int port)
{
	struct sockaddr_in	server;
	t_server			*result;

	result = (t_server*)malloc(sizeof(t_server));
	result->image_size = o.image_size;
	result->port = port;
	result->socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(result->port);
	le_error(bind(result->socket, (struct sockaddr*)&server, sizeof(server)));
	ft_putstr("Binded\n");
	listen(result->socket, 3);
	return (result);
}

void			accept_connection(t_thread *t)
{
	int					clnt_id;
	struct sockaddr_in	client;
	t_client			i;
	char				buf[256];

	clnt_id = sizeof(client);
	clnt_id = accept(t->server->socket, (struct sockaddr*)&client,
											(socklen_t*)&clnt_id);
	le_error(clnt_id);
	ft_putstr("Client #");
	ft_putnbr(t->id);
	ft_putstr(" connected.\n");
	i.id = t->id;
	i.json_len = t->json_len;
	i.max_peers = 0;
	i.line_size = 0;
	i.spp_per_call = 0;
	send(clnt_id, &i, sizeof(t_client), 0x2000);
	send_to_socket(clnt_id, (void*)t->json_file, t->json_len);
	t->clnt_socket = clnt_id;
	ft_bzero((void*)&buf, 256);
	recv(clnt_id, buf, 256, 0);
}
