/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 20:49:34 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/20 01:07:40 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				udp_connection(char *hostname, int portno, const char *last)
{
	t_udp		udp;

	udp.sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (udp.sockfd < 0)
		ft_error("ERROR opening socket");
	udp.server = gethostbyname(hostname);
	if (udp.server == NULL)
		ft_error("ERROR, no such host\n");
	ft_bzero((char*)&udp.serveraddr, sizeof(udp.serveraddr));
	udp.serveraddr.sin_family = AF_INET;
	bcopy((char *)udp.server->h_addr, (char*)&udp.serveraddr.sin_addr.s_addr,
														udp.server->h_length);
	udp.serveraddr.sin_port = htons(portno);
	udp.serverlen = sizeof(udp.serveraddr);
	sendto(udp.sockfd, last, strlen(last), 0,
							(struct sockaddr *)&udp.serveraddr, udp.serverlen);
	recvfrom(udp.sockfd, (void*)(&portno), 4, 0,
						(struct sockaddr*)&udp.serveraddr, &udp.serverlen);
	return (portno);
}

void			client_reinit(t_info *a)
{
	t_cl	*cl;

	cl = thread_get();
	free(a->scene);
	free(a->current_sample);
	free(a->camera);
	free(a->line_data);
	free_buffers(cl, a);
	send(a->server.socket, "ok", 2, 0x2000);
	client_init(a);
}

void			client_init(t_info *a)
{
	size_t		ret;

	ft_putstr("Recieving t_client-1\n");
	ret = recv(a->server.socket, (void*)&a->client, sizeof(t_client), 0);
	if (ret != sizeof(t_client))
		ft_error("recv t_client-1 failed");
	else
		ft_putstr("OK\n\n");
	a->json_file = (char*)malloc(a->client.json_len + 1);
	a->json_file[a->client.json_len] = '\0';
	ft_putstr("Recieving json configuration\n");
	if (recv_from_socket(a->server.socket, (void*)a->json_file,
														a->client.json_len))
		send(a->server.socket, "ok", 2, 0x2000);
	else
		ft_putstr("FAIL\n\n");
	ft_putstr("OK\n\n");
	ft_putstr("Recieving t_client-2\n");
	recv(a->server.socket, (void*)&a->client, sizeof(t_client), 0);
	ft_putstr("OK\n");
	a->line_data = (t_uch*)malloc(a->client.line_size * 4);
	init(a, a->json_file);
	free(a->json_file);
	send(a->server.socket, "ok", 2, 0x2000);
}

void			init(t_info *a, char *json_file)
{
	system("rm -f log");
	if ((a->log_fd = open("log.log", O_CREAT | O_RDWR, S_IWRITE | S_IREAD))
																		== -1)
		ft_putstr("Could not open log file");
	print_time(a->log_fd);
	init_scene(a);
	a->scene->image_width = a->client.width;
	a->scene->image_height = a->client.height;
	a->scene_is_valid = 1;
	parse_scene(a, json_file);
	ft_putendl_fd("Scene is valid", a->log_fd);
	close(a->log_fd);
	parse_texture(a);
	init_perlin(a, 800, 800);
	init_opencl(a);
}

void			quit(t_info *a)
{
	t_cl	*cl;

	cl = thread_get();
	free(a->scene);
	free(a->current_sample);
	free(a->camera);
	free(a->line_data);
	free_buffers(cl, a);
	close(a->server.socket);
	ft_putstr("Exit succesfully\n");
	exit(0);
}
