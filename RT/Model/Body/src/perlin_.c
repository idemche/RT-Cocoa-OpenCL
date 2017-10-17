/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:44:38 by hshakula          #+#    #+#             */
/*   Updated: 2017/09/01 15:29:27 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		normalize_perlin(t_info *a, int width, int height, int i)
{
	int y;
	int x;

	y = -1;
	while (++y < height)
	{
		x = -1;
		while (++x < width)
		{
			a->perlin.values[i] = (a->perlin.values[i] - a->perlin.min) /
											(a->perlin.max - a->perlin.min);
			i++;
		}
	}
}

double		perlin_noise(double x, double y, double frequency, double amplitude)
{
	double	total;
	double	p;
	int		n;
	int		i;

	n = 8;
	p = 0.6;
	total = 0;
	i = -1;
	while (++i <= n)
	{
		frequency = pow(2, i);
		amplitude = pow(p, i);
		total = total + interpolate_noise(x * frequency, y * frequency)
															* amplitude;
	}
	return (total);
}

void		init_perlin(t_info *a, int width, int height)
{
	int x;
	int y;
	int i;

	a->perlin.values = (cl_float*)malloc(sizeof(cl_float) * width * height);
	a->perlin.min = 0;
	a->perlin.max = 0;
	i = 0;
	y = -1;
	while (++y < height)
	{
		x = -1;
		while (++x < width)
		{
			a->perlin.values[i] = (cl_float)perlin_noise((double)x / 16,
													(double)y / 16, 0, 0);
			if (a->perlin.values[i] < a->perlin.min)
				a->perlin.min = a->perlin.values[i];
			if (a->perlin.values[i] > a->perlin.max)
				a->perlin.max = a->perlin.values[i];
			i++;
		}
	}
	normalize_perlin(a, width, height, 0);
}
