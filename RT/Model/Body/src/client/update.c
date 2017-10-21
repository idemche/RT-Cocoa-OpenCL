/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 20:49:34 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/20 13:56:26 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		update_cam(t_info *a)
{
	t_scene			scene;
	unsigned char	buf[512];

	send(a->server.socket, "cam", 3, 0x2000);
	bzero((void*)&buf, 512);
	recv(a->server.socket, buf, sizeof(t_camera), 0);
	memcpy(a->camera, buf, sizeof(t_camera));
	bzero((void*)&buf, 512);
	send(a->server.socket, "ok", 2, 0x2000);
	recv(a->server.socket, buf, sizeof(t_scene), 0);
	memcpy((void*)&scene, buf, sizeof(t_scene));
	a->scene->light_on = scene.light_on;
	a->scene->parallel_light = scene.parallel_light;
	a->scene->indirect_light = scene.indirect_light;
	a->scene->spotlight = scene.spotlight;
	a->scene->v_eff = scene.v_eff;
	a->scene->tone_mapper = scene.tone_mapper;
	a->scene->c_mode = scene.c_mode;
	send(a->server.socket, "ok", 2, 0x2000);
	a->update_camera = 1;
}

static void		update_scene(t_info *a)
{
	unsigned char	buf[512];
	size_t			ret;
	t_scene			scene;

	send(a->server.socket, "sce", 3, 0x2000);
	bzero((void*)&buf, 512);
	ret = recv(a->server.socket, buf, sizeof(t_scene), 0);
	if (ret != sizeof(t_scene))
		ft_putstr("Update scene: accepted only part of packet\n");
	memcpy((void*)&scene, buf, sizeof(t_scene));
	bzero((void*)&buf, 512);
	a->scene->light_on = scene.light_on;
	a->scene->parallel_light = scene.parallel_light;
	a->scene->indirect_light = scene.indirect_light;
	a->scene->spotlight = scene.spotlight;
	a->scene->v_eff = scene.v_eff;
	a->scene->tone_mapper = scene.tone_mapper;
	a->scene->c_mode = scene.c_mode;
	send(a->server.socket, "ok", 2, 0x2000);
	a->update_scene = 1;
}

void			client_update(t_info *a)
{
	char buf[256];

	send(a->server.socket, "ok", 2, 0x2000);
	bzero((void*)&buf, 256);
	recv(a->server.socket, buf, 256, 0);
	if (!ft_strncmp(buf, "camera", 6))
		update_cam(a);
	else if (!ft_strncmp(buf, "scene", 5))
		update_scene(a);
}
