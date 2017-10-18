/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 20:49:34 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/18 01:34:00 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		init_server(t_info *a)
{
	init_scene(a);
	init_server_info(a, a->json_file);
	return ;
}

void		server(t_info *a)
{
	a->json_len = get_file(a->scenes[a->num_scene], &a->json_file);
	if (!a->json_len)
		exit(2);
	init_threads(a, a->json_file, a->json_len);
	init_server(a);
	collect_peers(a);
	free(a->json_file);
	init_sdl(a);
	sdl_loop(a);
	destroy_sdl(a);
	exit_call(a);
	close(a->server.socket);
	exit(1);
}
