/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:44:38 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/19 15:55:10 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		rotate_cam_(t_info *a, int key)
{
	t_quaternion	q;

	if (key == SDLK_k)
	{
		q = init_quat(a->camera->up, -6 * a->scale_angle);
		a->camera->dir = quat_transform_vec3(q, a->camera->dir);
		normalise_vec3(&a->camera->dir);
		a->camera->right = cross_prod(a->camera->dir, a->camera->up);
	}
	else if (key == SDLK_o)
	{
		q = init_quat(a->camera->dir, 6 * a->scale_angle);
		a->camera->up = quat_transform_vec3(q, a->camera->up);
		normalise_vec3(&a->camera->up);
		a->camera->right = cross_prod(a->camera->dir, a->camera->up);
	}
	else if (key == SDLK_l)
	{
		q = init_quat(a->camera->dir, -6 * a->scale_angle);
		a->camera->up = quat_transform_vec3(q, a->camera->up);
		normalise_vec3(&a->camera->up);
		a->camera->right = cross_prod(a->camera->dir, a->camera->up);
	}
}

static void		rotate_cam(t_info *a, int key)
{
	t_quaternion	q;

	if (key == SDLK_u)
	{
		q = init_quat(a->camera->right, 6 * a->scale_angle);
		a->camera->dir = quat_transform_vec3(q, a->camera->dir);
		normalise_vec3(&a->camera->dir);
		a->camera->up = cross_prod(a->camera->right, a->camera->dir);
	}
	else if (key == SDLK_j)
	{
		q = init_quat(a->camera->right, -6 * a->scale_angle);
		a->camera->dir = quat_transform_vec3(q, a->camera->dir);
		normalise_vec3(&a->camera->dir);
		a->camera->up = cross_prod(a->camera->right, a->camera->dir);
	}
	else if (key == SDLK_i)
	{
		q = init_quat(a->camera->up, 6 * a->scale_angle);
		a->camera->dir = quat_transform_vec3(q, a->camera->dir);
		normalise_vec3(&a->camera->dir);
		a->camera->right = cross_prod(a->camera->dir, a->camera->up);
	}
	else if (key == SDLK_k || key == SDLK_l || key == SDLK_o)
		rotate_cam_(a, key);
}

static void		move_cam(t_info *a, int key)
{
	if (key == SDLK_q)
		a->camera->pos = add_vec3(a->camera->pos,
							mult_3(a->camera->up, 75 * a->scale_speed));
	if (key == SDLK_e)
		a->camera->pos = add_vec3(a->camera->pos,
							mult_3(a->camera->up, -75 * a->scale_speed));
	if (key == SDLK_w)
		a->camera->pos = add_vec3(a->camera->pos,
							mult_3(a->camera->dir, 75 * a->scale_speed));
	if (key == SDLK_a)
		a->camera->pos = add_vec3(a->camera->pos,
							mult_3(a->camera->right, -75 * a->scale_speed));
	if (key == SDLK_s)
		a->camera->pos = add_vec3(a->camera->pos,
							mult_3(a->camera->dir, -75 * a->scale_speed));
	if (key == SDLK_d)
		a->camera->pos = add_vec3(a->camera->pos,
							mult_3(a->camera->right, 75 * a->scale_speed));
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
	if (a->scene->visual_effect != k.visual_effect ||
		a->scene->tone_mapper != k.tone_mapper)
		a->update_scene = 1;
	if (k.light != a->scene->light_on ||
		k.indirect_light != a->scene->indirect_light ||
		k.parallel_light != a->scene->parallel_light ||
		k.spot_light != a->scene->spotlight || k.dof != a->scene->dof)
		a->update_camera = 1;
	a->scene->light_on = k.light;
	a->scene->indirect_light = k.indirect_light;
	a->scene->parallel_light = k.parallel_light;
	a->scene->spotlight = k.spot_light;
	a->scene->dof = k.dof;
	a->scene->visual_effect = k.visual_effect;
	a->scene->tone_mapper = k.tone_mapper;
	a->scale_angle = k.scale_angle;
	a->scale_speed = k.scale_speed;
	reset_keys(a);
}

void			handle_events(t_info *a, SDL_Event event, int key)
{
	key = event.key.keysym.sym;
	if (event.type == SDL_QUIT || key == SDLK_ESCAPE)
	{
		a->quit = 1;
		return ;
	}
	if (event.key.state != SDL_PRESSED || a->sequence.is_on)
		return ;
	if (key == SDLK_z)
		a->save_image = 1;
	if (key == SDLK_u || key == SDLK_i || key == SDLK_o ||
		key == SDLK_j || key == SDLK_k || key == SDLK_l)
	{
		a->update_camera = 1;
		rotate_cam(a, key);
	}
	if (key == SDLK_q || key == SDLK_w || key == SDLK_e ||
		key == SDLK_a || key == SDLK_s || key == SDLK_d)
	{
		a->update_camera = 1;
		move_cam(a, key);
	}
	return ;
}
