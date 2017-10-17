/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence_call.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:44:38 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/17 17:13:55 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		change_camera(t_info *a)
{
	t_quaternion		q;

	q = a->sequence.q;
	q.w *= -1;
	a->camera->dir = quat_transform_vec3(q, a->camera->dir);
	normalise_vec3(&a->camera->dir);
	a->camera->up = quat_transform_vec3(q, a->camera->up);
	normalise_vec3(&a->camera->up);
	a->camera->right = quat_transform_vec3(q, a->camera->right);
	normalise_vec3(&a->camera->right);
	a->camera->pos = add_vec3(mult_3(a->camera->dir, -1 * a->len),
														a->sequence.look_at);
}

void			sequence_call(t_info *a)
{
	char	buffer[256];

	if (a->sequence.frame_max + 1 == a->sequence.frame_n)
	{
		strlcat(a->sequence.buf, " animation.gif",
											a->sequence.frame_max * 19 + 100);
		system(a->sequence.buf);
		ft_error("Images are done");
	}
	render_call(a);
	change_camera(a);
	update_camera_call(a);
	get_image(a);
	bzero(buffer, 256);
	strcpy(buffer, "image");
	strcat(buffer, ft_itoa(a->sequence.frame_n));
	strcat(buffer, ".png");
	save_image(a, buffer);
	strcat(buffer, " ");
	strlcat(a->sequence.buf, buffer, a->sequence.frame_max * 19 + 100);
	a->sequence.frame_n++;
}
