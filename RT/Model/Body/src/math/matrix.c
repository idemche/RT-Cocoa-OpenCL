/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 19:24:23 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/17 19:54:56 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		get_coeffs(t_matrix *m, t_inv_matrix_coeffs *c)
{
	float	det;

	c->d1 = m->b.y * m->c.z - m->c.y * m->b.z;
	c->d2 = m->b.x * m->c.z - m->b.z * m->c.x;
	c->d3 = m->b.x * m->c.y - m->c.x * m->b.y;
	det = m->a.x * c->d1 - m->a.y * c->d2 + m->a.z * c->d3;
	c->invdet = 1.0f / det;
}

t_matrix		inverse_matrix(t_matrix *m)
{
	t_matrix			minv;
	t_inv_matrix_coeffs	c;

	get_coeffs(m, &c);
	minv.a.x = c.d1 * c.invdet;
	minv.a.y = (m->a.z * m->c.y - m->a.y * m->c.z) * c.invdet;
	minv.a.z = (m->a.y * m->b.z - m->a.z * m->b.y) * c.invdet;
	minv.b.x = -c.d2 * c.invdet;
	minv.b.y = (m->a.x * m->c.z - m->a.z * m->c.x) * c.invdet;
	minv.b.z = (m->b.x * m->a.z - m->a.x * m->b.z) * c.invdet;
	minv.c.x = c.d3 * c.invdet;
	minv.c.y = (m->c.x * m->a.y - m->a.x * m->c.y) * c.invdet;
	minv.c.z = (m->a.x * m->b.y - m->b.x * m->a.y) * c.invdet;
	return (minv);
}

t_matrix		init_transform_matrix(VEC3 e1, VEC3 e2, VEC3 e3)
{
	t_matrix m;

	m.a.x = e1.x;
	m.b.x = e1.y;
	m.c.x = e1.z;
	m.a.y = e2.x;
	m.b.y = e2.y;
	m.c.y = e2.z;
	m.a.z = e3.x;
	m.b.z = e3.y;
	m.c.z = e3.z;
	return (m);
}
