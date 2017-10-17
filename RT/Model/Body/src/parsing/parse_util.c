/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:53:27 by hshakula          #+#    #+#             */
/*   Updated: 2017/08/31 18:53:04 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			parse_color(VEC3 *result, cJSON *color)
{
	cJSON		*r;
	cJSON		*g;
	cJSON		*b;

	r = cJSON_GetObjectItemCaseSensitive(color, "r");
	g = cJSON_GetObjectItemCaseSensitive(color, "g");
	b = cJSON_GetObjectItemCaseSensitive(color, "b");
	if (!cJSON_IsNumber(r) || !cJSON_IsNumber(g) || !cJSON_IsNumber(b))
		ft_error("RGB error");
	*result = i_3(r->valuedouble, g->valuedouble, b->valuedouble);
	if (result->x > 1 || result->x < 0 ||
		result->y > 1 || result->y < 0 ||
		result->z > 1 || result->z < 0)
		ft_error("RGB error");
}

void			parse_emission(VEC3 *result, cJSON *color)
{
	cJSON		*r;
	cJSON		*g;
	cJSON		*b;

	r = cJSON_GetObjectItemCaseSensitive(color, "r");
	g = cJSON_GetObjectItemCaseSensitive(color, "g");
	b = cJSON_GetObjectItemCaseSensitive(color, "b");
	if (!cJSON_IsNumber(r) || !cJSON_IsNumber(g) || !cJSON_IsNumber(b))
		ft_error("Emission error");
	*result = i_3(r->valuedouble, g->valuedouble, b->valuedouble);
	if (result->x < 0 || result->y < 0 || result->z < 0)
		ft_error("Emission error");
}

void			parse_point(VEC3 *result, cJSON *point)
{
	cJSON		*x;
	cJSON		*y;
	cJSON		*z;

	x = cJSON_GetObjectItemCaseSensitive(point, "x");
	y = cJSON_GetObjectItemCaseSensitive(point, "y");
	z = cJSON_GetObjectItemCaseSensitive(point, "z");
	if (!cJSON_IsNumber(x) || !cJSON_IsNumber(y) || !cJSON_IsNumber(z))
		ft_error("Point error");
	*result = i_3(x->valuedouble, y->valuedouble, z->valuedouble);
}

bool			check_vec3(VEC3 v)
{
	if (v.x == 0.0 && v.y == 0.0 && v.z == 0.0)
		return (FALSE);
	else
		return (TRUE);
}
