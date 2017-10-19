/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:44:38 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/19 19:15:59 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "rt.h"
# include <sys/socket.h>
# include <arpa/inet.h>
# include <pthread.h>
# include <netinet/in.h>
# include <netdb.h>

# define BUFF_SIZE 256

typedef struct	s_udp
{
	struct sockaddr_in	clientaddr;
	char				*hostaddrp;
	int					sockfd;
	t_uint				serverlen;
	struct sockaddr_in	serveraddr;
	struct hostent		*server;
}				t_udp;

typedef struct	s_server
{
	int			image_size;
	int			max_peers;
	int			line_size;
	int			socket;
	int			port;
}				t_server;

typedef struct	s_thread
{
	pthread_t	thread;
	int			id;
	int			clnt_socket;
	size_t		json_len;
	char		*json_file;
	t_server	*server;
	t_info		*a;
	t_uch		*data;
}				t_thread;

void			server(t_info *a);
void			init_server(t_info *a);
void			reinit_server(t_info *a);
void			init_server_info(t_info *a, char *json_file);
void			init_threads(t_info *a, char *json_file, size_t json_len);
void			collect_peers(t_info *a);
t_server		*create_tcp_server(t_server o, int port);
t_server		create_udp_server(t_info *a);
void			accept_connection(t_thread *t);
void			render_call(t_info *a);
void			sequence_call(t_info *a);
void			exit_call(t_info *a);
void			update_camera_call(t_info *a);
void			update_scene_call(t_info *a);
int				recv_from_socket(int socket, void *data, size_t size);
int				send_to_socket(int sock, void *data, size_t size);
void			send_camera(t_thread *t);
void			le_error(int error);

#endif
