/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 13:43:19 by hshakula          #+#    #+#             */
/*   Updated: 2016/12/12 17:43:39 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t		i;
	const char	*s1_ptr;
	const char	*s2_ptr;

	s1_ptr = s1;
	s2_ptr = s2;
	i = 0;
	while (i < n)
	{
		if (s1_ptr[i] != s2_ptr[i])
			return ((unsigned char)s1_ptr[i] - (unsigned char)s2_ptr[i]);
		i++;
	}
	return (0);
}
