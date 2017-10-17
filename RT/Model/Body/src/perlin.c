/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:44:38 by hshakula          #+#    #+#             */
/*   Updated: 2017/09/01 15:24:31 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		cos_interpolate(double v1, double v2, double a)
{
	double angle;
	double prc;

	angle = a * M_PI;
	prc = (1.0f - cos(angle)) * 0.5f;
	return (v1 * (1.0f - prc) + v2 * prc);
}

double		noise(int x, int y)
{
	int n;

	n = (x + y * 57);
	n = (n << 13) ^ n;
	return (1.0 - ((n * (n * n * 15731 + 789221) + 1376312589) &
												0x7fffffff) / 1073741824.0);
}

double		smoothed_noise(int x, int y)
{
	double corners;
	double sides;
	double center;

	corners = (noise(x - 1, y - 1) + noise(x + 1, y - 1) +
						noise(x - 1, y + 1) + noise(x + 1, y + 1)) / 16;
	sides = (noise(x - 1, y) + noise(x + 1, y) +
								noise(x, y - 1) + noise(x, y + 1)) / 8;
	center = noise(x, y) / 4;
	return (corners + sides + center);
}

double		interpolate_noise(double x, double y)
{
	t_perlin p;

	p.integer_x = (int)x;
	p.fractional_x = x - p.integer_x;
	p.integer_y = (int)y;
	p.fractional_y = y - p.integer_y;
	p.v1 = smoothed_noise(p.integer_x, p.integer_y);
	p.v2 = smoothed_noise(p.integer_x + 1, p.integer_y);
	p.v3 = smoothed_noise(p.integer_x, p.integer_y + 1);
	p.v4 = smoothed_noise(p.integer_x + 1, p.integer_y + 1);
	p.i1 = cos_interpolate(p.v1, p.v2, p.fractional_x);
	p.i2 = cos_interpolate(p.v3, p.v4, p.fractional_x);
	return (cos_interpolate(p.i1, p.i2, p.fractional_y));
}
