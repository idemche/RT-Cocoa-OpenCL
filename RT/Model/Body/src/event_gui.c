/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_gui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:44:38 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/20 14:56:59 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		gui_update_camera(t_info *a, t_keys k)
{
	// a->scene->c_mode = k.c_mode;
	// a->camera->focal_length = k.fl;
	// a->camera->aperture = k.aperture;
	a->scale_angle = k.scale_angle;
	a->scale_speed = k.scale_speed;
	return (0);
	// return (k.c_mode != a->scene->c_mode || k.aperture != a->camera->aperture || k.fl != a->camera->focal_length);
}

void			update_from_gui(t_info *a, t_keys k)
{
	if (k.change_scene != -1)
	{
		a->update_map = 1;
		a->num_scene = k.change_scene;
		reset_keys(a);
		return ;
	}
	if (a->scene->v_eff != k.visual_effect ||
		a->scene->tone_mapper != k.tone_mapper)
		a->update_scene = 1;
	if (k.light != a->scene->light_on ||
		k.indirect_light != a->scene->indirect_light ||
		k.parallel_light != a->scene->parallel_light ||
		k.spot_light != a->scene->spotlight || gui_update_camera(a, k)) //
		a->update_camera = 1;
	a->scene->light_on = k.light;
	a->scene->indirect_light = k.indirect_light;
	a->scene->parallel_light = k.parallel_light;
	a->scene->spotlight = k.spot_light;
	a->scene->v_eff = k.visual_effect;
	a->scene->tone_mapper = k.tone_mapper;
	reset_keys(a);
}

