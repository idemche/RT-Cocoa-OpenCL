/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:44:38 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/19 19:16:14 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PERLIN_H
# define PERLIN_H

# include "rt.h"

typedef struct	s_perlin
{
	cl_float	*values;
	float		min;
	float		max;
	int			integer_x;
	int			integer_y;
	double		fractional_x;
	double		fractional_y;
	double		v1;
	double		v2;
	double		v3;
	double		v4;
	double		i1;
	double		i2;
}				t_perlin;

void			init_perlin(t_info *a, int width, int height);
double			interpolate_noise(double x, double y);

#endif
