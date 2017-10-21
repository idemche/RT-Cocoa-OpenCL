/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:52:49 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/20 13:45:13 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		init_cam(t_info *a)
{
	if (!a->scene_is_valid)
		return ;
	if (a->camera->dir.x != 0.0 && a->camera->dir.y != 0.0)
	{
		a->camera->right = cross_prod(a->camera->dir, i_3(0, 0, 1));
		normalise_vec3(&a->camera->right);
		a->camera->up = cross_prod(a->camera->right, a->camera->dir);
		normalise_vec3(&a->camera->up);
	}
	else
	{
		a->camera->up = cross_prod((fabs(a->camera->dir.x) > 1e-6 ?
			i_3(0, 1, 0) : i_3(1, 0, 0)), a->camera->dir);
		normalise_vec3(&a->camera->up);
		a->camera->right = cross_prod(a->camera->dir, a->camera->up);
		normalise_vec3(&a->camera->right);
	}
}

static void	validate_cam_(t_info *a, t_json_cam *jc)
{
	if (!(cJSON_IsNumber(jc->fov) && jc->fov->valuedouble >= 25
			&& jc->fov->valuedouble < 90))
	{
		warning(a, "invalid camera fov, default value 66.6");
		a->camera->fov = 66.6;
	}
	else
		a->camera->fov = jc->fov->valuedouble;
	if (!(cJSON_IsNumber(jc->t)) || jc->t->valuedouble < 0)
	{
		warning(a, "invalid camera exposition time, default 0");
		a->camera->t = 0.0;
	}
	else
		a->camera->t = jc->t->valuedouble;
}

static void	validate_cam(t_info *a, t_json_cam *jc)
{
	validate_cam_(a, jc);
	if (!cJSON_IsNumber(jc->aperture) || jc->aperture->valuedouble < 0.0)
	{
		warning(a, "invalid aperture value, default 10");
		a->camera->aperture = 10.0;
	}
	else
		a->camera->aperture = jc->aperture->valuedouble;
	if (!cJSON_IsNumber(jc->focal) || jc->focal->valuedouble < 1.0)
	{
		warning(a, "invalid focal length value, default 400");
		a->camera->focal_length = 400.0;
	}
	else
		a->camera->focal_length = jc->focal->valuedouble;
	a->camera->aspectratio = (float)a->scene->image_width /
												(float)(a->scene->image_height);
	a->camera->angle = tan(M_PI * 0.5 * a->camera->fov / 180);
}

void		cam_parsing(t_info *a, cJSON *root)
{
	t_json_cam	jc;

	jc.cam = cJSON_GetObjectItemCaseSensitive(root, "cam");
	a->camera = (t_camera*)malloc(sizeof(t_camera));
	jc.dir = cJSON_GetObjectItemCaseSensitive(jc.cam, "dir");
	jc.pos = cJSON_GetObjectItemCaseSensitive(jc.cam, "point");
	jc.fov = cJSON_GetObjectItemCaseSensitive(jc.cam, "fov");
	jc.focal = cJSON_GetObjectItemCaseSensitive(jc.cam, "focal length");
	jc.aperture = cJSON_GetObjectItemCaseSensitive(jc.cam, "aperture");
	jc.t = cJSON_GetObjectItemCaseSensitive(jc.cam, "exposition time");
	if (!parse_point(&(a->camera->dir), jc.dir))
		scene_error(a, "missing camera dir");
	a->sequence.look_at = a->camera->dir;
	if (!parse_point(&a->camera->pos, jc.pos))
		scene_error(a, "missing camera pos");
	a->camera->dir = sub_vec3(a->camera->dir, a->camera->pos);
	a->len = sqrtf(dot_3(a->camera->dir, a->camera->dir));
	if (!check_vec3(a->camera->dir))
		scene_error(a, "invalid camera dir");
	else
		normalise_vec3(&a->camera->dir);
	a->camera->inv_width = 1.0 / (float)a->scene->image_width;
	a->camera->inv_height = 1.0 / (float)a->scene->image_height;
	validate_cam(a, &jc);
	init_cam(a);
}
