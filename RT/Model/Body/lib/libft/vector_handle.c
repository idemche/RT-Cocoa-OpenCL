/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 15:11:46 by hshakula          #+#    #+#             */
/*   Updated: 2017/09/30 20:54:38 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

cl_float	dot_3(VEC3 v1, VEC3 v2)
{
	cl_float	res;

	res = v1.x * v2.x;
	res += v1.y * v2.y;
	res += v1.z * v2.z;
	return (res);
}

void		normalise_vec3(VEC3 *v)
{
	cl_float		len;

	len = 1 / sqrtf(dot_3(*v, *v));
	v->x *= len;
	v->y *= len;
	v->z *= len;
}

VEC3		i_3(cl_float x, cl_float y, cl_float z)
{
	VEC3	res;

	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}

VEC3		mult_3(VEC3 vector, cl_float c)
{
	VEC3	res;

	res.x = vector.x * c;
	res.y = vector.y * c;
	res.z = vector.z * c;
	return (res);
}

VEC3		sub_vec3(VEC3 v1, VEC3 v2)
{
	VEC3	res;

	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	res.z = v1.z - v2.z;
	return (res);
}
