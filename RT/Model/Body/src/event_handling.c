/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:44:38 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/20 01:16:36 by admin            ###   ########.fr       */
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

static void		scene_events(t_info *a, int k)
{
	if (k == SDLK_t || k == SDLK_r)
	{
		a->update_scene = 1;
		if (k == SDLK_t)
			a->scene->v_eff += (a->scene->v_eff == 3) ? -3 : 1;
		if (k == SDLK_r)
			a->scene->tone_mapper += (a->scene->tone_mapper == 2) ? -2 : 1;
	}
	if (k == SDLK_x || k == SDLK_y || k == SDLK_b || k == SDLK_n ||
		k == SDLK_m)
	{
		a->update_camera = 1;
		if (k == SDLK_y)
			a->scene->c_mode += (a->scene->c_mode == 2) ? -2 : 1;
		if (k == SDLK_x)
			a->scene->light_on = (a->scene->light_on) ? 0 : 1;
		if (k == SDLK_b)
			a->scene->parallel_light = (a->scene->parallel_light) ? 0 : 1;
		if (k == SDLK_n)
			a->scene->indirect_light = (a->scene->indirect_light) ? 0 : 1;
		if (k == SDLK_m)
			a->scene->spotlight = (a->scene->spotlight) ? 0 : 1;
	}
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
	scene_events(a, key);
}
