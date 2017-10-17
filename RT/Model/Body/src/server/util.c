/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 20:49:34 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/16 14:42:17 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#define BUFFSIZE 8192

void			le_error(int error)
{
	if (error == -1)
	{
		perror("Error");
		exit(-1);
	}
}

void			send_camera(t_thread *t)
{
	char		response[256];

	send(t->clnt_socket, "camera", 6, 0x2000);
	bzero((void*)&response, 256);
	recv(t->clnt_socket, response, 256, 0);
	if (!ft_strncmp(response, "cam", 3))
	{
		send(t->clnt_socket, t->a->camera, sizeof(t_camera), 0x2000);
		bzero((void*)&response, 256);
		recv(t->clnt_socket, response, 256, 0);
		if (!ft_strncmp(response, "ok", 2))
		{
			send(t->clnt_socket, t->a->scene, sizeof(t_scene), 0x2000);
			bzero((void*)&response, 256);
			recv(t->clnt_socket, response, 256, 0);
			if (ft_strncmp(response, "ok", 2))
				printf("Thread_camera_update [%d]: smthg went wrong\n", t->id);
		}
		else
			printf("Thread_camera_update [%d]: smthg went wrong 2\n", t->id);
	}
	else
		printf("Thread_camera_update [%d]: something went wrong 1\n", t->id);
}

int				send_to_socket(int sock, void *data, size_t size)
{
	int	ret[2];

	ret[0] = BUFFSIZE;
	while (1)
	{
		if (size < BUFFSIZE)
			ret[0] = (int)size;
		ret[1] = (int)send(sock, data, ret[0], 0x2000);
		if (ret[1] < 0)
		{
			perror("send_to_socket");
			return (0);
		}
		data = data + ret[1];
		if (ret[1] >= (int)size)
			break ;
		size -= ret[1];
	}
	return (1);
}

int				recv_from_socket(int socket, void *data, size_t size)
{
	t_uch	buff[BUFFSIZE];
	int		ret[2];
	size_t	i;

	ret[0] = BUFFSIZE;
	i = 0;
	while (1)
	{
		bzero(buff, BUFFSIZE);
		if (size - i < BUFFSIZE)
			ret[0] = (int)(size - i);
		ret[1] = (int)recv(socket, buff, ret[0], 0);
		if (ret[1] < 0)
		{
			perror("recv_from_socket");
			return (0);
		}
		memcpy(data + i, buff, ret[1]);
		i += ret[1];
		if (i == size)
			break ;
	}
	return (1);
}
