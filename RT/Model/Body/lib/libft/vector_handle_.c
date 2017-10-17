/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_handle_.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 15:11:46 by hshakula          #+#    #+#             */
/*   Updated: 2017/09/30 20:54:32 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

VEC3		cross_prod(VEC3 v1, VEC3 v2)
{
	VEC3 c;

	c.x = v1.y * v2.z - v1.z * v2.y;
	c.y = v1.z * v2.x - v1.x * v2.z;
	c.z = v1.x * v2.y - v1.y * v2.x;
	return (c);
}

VEC3		add_vec3(VEC3 v1, VEC3 v2)
{
	VEC3 v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;
	return (v);
}
