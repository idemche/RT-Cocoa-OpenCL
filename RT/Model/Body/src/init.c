/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:44:38 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/20 14:05:55 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			init_scene_(t_info *a)
{
	a->scene->amount_of_spotlights = 0;
	a->scene->amount_of_objects = 0;
	a->scene->amount_of_spotlights = 0;
	a->scene->amount_of_albedo_textures = 0;
	a->scene->n_negative_obj = 0;
	a->scene->env_map = 0;
	a->scene->radiance_env_map = 0;
	a->environment_map = NULL;
}

void				init_scene(t_info *a)
{
	a->scene_is_valid = 1;
	a->scene = (t_scene*)malloc(sizeof(t_scene));
	a->current_sample = (cl_int*)malloc(sizeof(cl_int));
	if (!a->current_sample)
		ft_error("Malloc error");
	a->scale_angle = 1.0;
	a->scale_speed = 1.0;
	a->scene->light_on = 0;
	a->scene->indirect_light = 0;
	a->scene->spotlight = 0;
	a->scene->parallel_light = 0;
	a->scene->tone_mapper = STANDARD;
	a->scene->c_mode = 0;
	a->scene->v_eff = 0;
	a->scene->node_id = (char)a->client.id;
	a->scene->amount_of_nodes = a->client.max_peers;
	a->update_camera = 0;
	a->update_map = 0;
	a->update_scene = 0;
	*(a->current_sample) = 0;
	a->scene->n_negative_obj = 0;
	bzero(a->scene->dummy, 13);
	reset_keys(a);
	init_scene_(a);
}

void				reset_keys(t_info *a)
{
	a->keys.update = 0;
	a->keys.change_scene = -1;
	a->keys.light = 0;
	a->keys.indirect_light = 0;
	a->keys.parallel_light = 0;
	a->keys.spot_light = 0;
	a->keys.c_mode = 0;
	a->keys.visual_effect = 0;
	a->keys.tone_mapper = 0;
	a->keys.scale_speed = 1.0;
	a->keys.scale_angle = 1.0;
	a->keys.fl = 400.0;
	a->keys.aperture = 0.0;
}
