/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 19:24:23 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/17 19:54:36 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_quaternion	invert_quat(t_quaternion q)
{
	t_quaternion	res;

	res.w = q.w;
	res.v = mult_3(q.v, -1);
	return (res);
}

t_quaternion	quat_mult_quat(t_quaternion q1, t_quaternion q2)
{
	t_quaternion	res;

	res.w = q1.w * q2.w - q1.v.x * q2.v.x - q1.v.y * q2.v.y - q1.v.z * q2.v.z;
	res.v.x = q1.w * q2.v.x + q1.v.x * q2.w + q1.v.y * q2.v.z - q1.v.z * q2.v.y;
	res.v.y = q1.w * q2.v.y - q1.v.x * q2.v.z + q1.v.y * q2.w + q1.v.z * q2.v.x;
	res.v.z = q1.w * q2.v.z + q1.v.x * q2.v.y - q1.v.y * q2.v.x + q1.v.z * q2.w;
	return (res);
}

t_quaternion	quat_mult_3(t_quaternion q, VEC3 v)
{
	t_quaternion	res;

	res.w = -q.v.x * v.x - q.v.y * v.y - q.v.z * v.z;
	res.v.x = q.w * v.x + q.v.y * v.z - q.v.z * v.y;
	res.v.y = q.w * v.y - q.v.x * v.z + q.v.z * v.x;
	res.v.z = q.w * v.z + q.v.x * v.y - q.v.y * v.x;
	return (res);
}

VEC3			quat_transform_vec3(t_quaternion q, VEC3 v)
{
	t_quaternion	tmp;

	tmp = quat_mult_3(q, v);
	tmp = quat_mult_quat(tmp, invert_quat(q));
	return (tmp.v);
}

t_quaternion	init_quat(VEC3 v, cl_float w)
{
	t_quaternion		new_quat;
	cl_float			len;

	normalise_vec3(&v);
	new_quat.v = mult_3(v, sin(RAD(w) / 2));
	new_quat.w = cos(RAD(w) / 2.0);
	len = 1 / sqrtf(1 + new_quat.w * new_quat.w);
	new_quat.w *= len;
	new_quat.v = mult_3(new_quat.v, len);
	return (new_quat);
}
