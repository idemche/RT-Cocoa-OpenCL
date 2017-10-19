/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 20:49:34 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/19 21:05:51 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		establish_connection(t_info *a, char *buffer)
{
	int					sock;
	struct sockaddr_in	server;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		ft_putstr("Could not create socket\n");
	else
		ft_putstr("Socket created\n");
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(buffer);
	server.sin_port = htons(a->server.port);
	if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0)
	{
		perror("connect failed. Error");
		return ;
	}
	puts("Connected\n");
	a->server.socket = sock;
}

static int		validate_params(char **av)
{
	struct sockaddr_in	sa;

	if (__builtin_strcmp(av[1], "l"))
	{
		if (!inet_pton(AF_INET, av[1], &(sa.sin_addr)))
			return (0);
	}
	return (1);
}

int				main(int ac, char **av)
{
	t_info	*a;
	char	*ip_;

	if (ac == 3)
	{
		a = (t_info*)malloc(sizeof(t_info));
		a->is_validating = 0;
		if (!validate_params(av))
			ft_usage();
		if (!__builtin_strcmp(av[1], "l"))
			ip_ = "127.0.0.1";
		else
			ip_ = av[1];
		a->server.port = 4444;
		a->server.port = udp_connection(ip_, a->server.port, av[2]);
		establish_connection(a, ip_);
		client_init(a);
		client_loop(a);
	}
	else
		ft_usage();
	return (0);
}
