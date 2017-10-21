/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_video_sequence.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:52:49 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/19 15:23:22 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	sequence_util(t_info *a)
{
	double			alpha;

	a->sequence.frame_n = 0;
	a->sequence.frame_max = a->sequence.fps * a->sequence.t;
	alpha = 360.0 / a->sequence.frame_max;
	a->sequence.q = init_quat(a->sequence.axis, alpha);
	a->sequence.buf = (char *)malloc(a->sequence.frame_max * 19 + 100);
	ft_bzero(a->sequence.buf, a->sequence.frame_max * 19 + 100);
	ft_strcpy(a->sequence.buf, "convert -dispose none -delay 1x30 ");
}

void		sequence_parse(t_info *a, cJSON *root)
{
	t_json_sequence	s;

	s.s = cJSON_GetObjectItemCaseSensitive(root, "Video sequence");
	if (!s.s)
		return ;
	s.is_on = cJSON_GetObjectItemCaseSensitive(s.s, "On/Off");
	if (!cJSON_IsBool(s.is_on))
		ft_error("On/Off field must be true or false");
	if ((a->sequence.is_on = s.is_on->valueint) == 0)
		return ;
	s.axis = cJSON_GetObjectItemCaseSensitive(s.s, "axis");
	s.time = cJSON_GetObjectItemCaseSensitive(s.s, "time");
	s.fps = cJSON_GetObjectItemCaseSensitive(s.s, "fps");
	if (!parse_point(&a->sequence.axis, s.axis))
		scene_error(a, "video sequence - invalid axis");
	if (!check_vec3(a->sequence.axis))
		ft_error("Invalid axis in video sequence configuration");
	normalise_vec3(&a->sequence.axis);
	if (!cJSON_IsNumber(s.time) || !cJSON_IsNumber(s.fps) ||
		s.time->valuedouble < 1.0 || s.time->valuedouble > 16.0 ||
		s.fps->valueint < 30 || s.fps->valueint > 90)
		ft_error("Video sequence configuration error");
	a->sequence.fps = s.fps->valueint;
	a->sequence.t = s.time->valuedouble;
	sequence_util(a);
}
