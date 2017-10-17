/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 20:49:34 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/11 16:49:46 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	client_loop(t_info *a)
{
	char	instruction[256];

	ft_putstr("Client loop\n\n");
	while (1)
	{
		bzero((void*)(&instruction), 256);
		recv(a->server.socket, instruction, 256, 0);
		if (!ft_strncmp(instruction, "render", 6))
			client_render(a);
		else if (!ft_strncmp(instruction, "update", 6))
			client_update(a);
		else if (!ft_strncmp(instruction, "exit", 4))
			quit(a);
		else if (!ft_strncmp(instruction, "reinit", 6))
			client_reinit(a);
		else
			send(a->server.socket, "fail", 4, 0);
	}
}
