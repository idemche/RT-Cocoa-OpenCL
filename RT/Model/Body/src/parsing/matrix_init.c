/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:53:16 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/21 02:49:56 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		write_transform_matrix_to_object(t_object *object)
{
	t_matrix	m;

	object->edge0 = cross_prod(object->dir, (fabs(object->dir.x) > 1e-6 ?
												i_3(0, 1, 0) : i_3(1, 0, 0)));
	normalise_vec3(&object->edge0);
	object->edge1 = cross_prod(object->dir, object->edge0);
	normalise_vec3(&object->edge1);
	m = init_transform_matrix(object->edge0, object->edge1, object->dir);
	m = inverse_matrix(&m);
	object->a = m.a;
	object->b = m.b;
	object->c = m.c;
}
