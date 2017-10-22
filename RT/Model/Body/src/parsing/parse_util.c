/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:53:27 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/19 15:24:52 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			warning(t_info *a, char *str)
{
	ft_putstr_fd("Warning: ", a->log_fd);
	ft_putendl_fd(str, a->log_fd);
}

void			parse_color(t_info *a, int i, VEC3 *result, cJSON *color)
{
	cJSON		*r;
	cJSON		*g;
	cJSON		*b;

	r = cJSON_GetObjectItemCaseSensitive(color, "r");
	g = cJSON_GetObjectItemCaseSensitive(color, "g");
	b = cJSON_GetObjectItemCaseSensitive(color, "b");
	if (!r && !g && !b)
	{
		object_warning(a, i, "color field missing, default white");
		*result = i_3(1, 1, 1);
	}
	else if (!cJSON_IsNumber(r) || !cJSON_IsNumber(g) || !cJSON_IsNumber(b) ||
		r->valuedouble > 1 || r->valuedouble < 0 || g->valuedouble > 1 ||
		g->valuedouble < 0 || b->valuedouble > 1 || b->valuedouble < 0)
	{
		object_error(a, i, "RGB must be in range [0;1]");
		*result = i_3(0, 0, 0);
	}
	else
		*result = i_3(r->valuedouble, g->valuedouble, b->valuedouble);
}

void			parse_emission(t_info *a, VEC3 *result, cJSON *color)
{
	cJSON		*r;
	cJSON		*g;
	cJSON		*b;

	r = cJSON_GetObjectItemCaseSensitive(color, "r");
	g = cJSON_GetObjectItemCaseSensitive(color, "g");
	b = cJSON_GetObjectItemCaseSensitive(color, "b");
	if (!cJSON_IsNumber(r) || !cJSON_IsNumber(g) || !cJSON_IsNumber(b) ||
		r->valuedouble < 0 || g->valuedouble < 0 || b->valuedouble < 0)
	{
		warning(a, "invalid emission, default 0");
		*result = i_3(0, 0, 0);
	}
	else
		*result = i_3(r->valuedouble, g->valuedouble, b->valuedouble);
}

int				parse_point(VEC3 *result, cJSON *point)
{
	cJSON		*x;
	cJSON		*y;
	cJSON		*z;

	x = cJSON_GetObjectItemCaseSensitive(point, "x");
	y = cJSON_GetObjectItemCaseSensitive(point, "y");
	z = cJSON_GetObjectItemCaseSensitive(point, "z");
	if (!cJSON_IsNumber(x) || !cJSON_IsNumber(y) || !cJSON_IsNumber(z))
	{
		*result = i_3(0, 0, 0);
		return (0);
	}
	*result = i_3(x->valuedouble, y->valuedouble, z->valuedouble);
	return (1);
}

bool			check_vec3(VEC3 v)
{
	if (v.x == 0.0 && v.y == 0.0 && v.z == 0.0)
		return (FALSE);
	else
		return (TRUE);
}
