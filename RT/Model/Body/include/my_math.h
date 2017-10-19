/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:44:38 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/19 19:15:49 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_MATH_H
# define MY_MATH_H

# include <math.h>
# include "rt.h"

# define RAD(x) (x * M_PI / 180.0)

typedef struct	s_matrix
{
	VEC3		a;
	VEC3		b;
	VEC3		c;
}				t_matrix;

typedef struct	s_inv_matrix_coeffs
{
	float		d1;
	float		d2;
	float		d3;
	float		invdet;
}				t_inv_matrix_coeffs;

typedef struct	s_quaternion
{
	float		w;
	VEC3		v;
}				t_quaternion;

t_quaternion	init_quat(VEC3 v, cl_float w);
void			normalise_quat(t_quaternion *q);
t_quaternion	invert_quat(t_quaternion q);
t_quaternion	quat_mult_quat(t_quaternion q1, t_quaternion q2);
t_quaternion	quat_mult_3(t_quaternion q, VEC3 v);
VEC3			quat_transform_vec3(t_quaternion q, VEC3 v);

t_matrix		inverse_matrix(t_matrix *m);
t_matrix		init_transform_matrix(VEC3 e1, VEC3 e2, VEC3 e3);

#endif
