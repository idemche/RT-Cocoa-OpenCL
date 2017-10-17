/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_call.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 20:49:34 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/16 14:42:23 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	*thread_exit(void *thread_)
{
	t_thread	*thread;

	thread = (t_thread*)thread_;
	send(thread->clnt_socket, "exit", 4, 0x2000);
	return (NULL);
}

void		exit_call(t_info *a)
{
	int		i;

	i = -1;
	while (++i < a->server.max_peers)
	{
		pthread_create(&(a->threads[i].thread), NULL, thread_exit,
			&(a->threads[i]));
	}
	i = -1;
	while (++i < a->server.max_peers)
		pthread_join(a->threads[i].thread, NULL);
}
