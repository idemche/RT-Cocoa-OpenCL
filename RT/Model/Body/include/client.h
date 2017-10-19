/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:44:38 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/19 19:15:44 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include "rt.h"

# define BUFF_SIZE 256

typedef struct	s_client
{
	int			id;
	size_t		json_len;
	int			line_size;
	int			max_peers;
	int			spp_per_call;
	int			width;
	int			height;
}				t_client;

void			client_init(t_info *a);
void			client_reinit(t_info *a);
void			client_render(t_info *a);
void			client_update(t_info *a);
void			client_loop(t_info *a);
int				udp_connection(char *hostname, int portno, const char *last);

#endif
