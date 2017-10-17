/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 13:43:19 by hshakula          #+#    #+#             */
/*   Updated: 2016/12/12 17:43:39 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	size_t		i;
	const char	*s2_ptr;
	char		*s1_ptr;

	s2_ptr = (const char*)s2;
	s1_ptr = (char*)s1;
	if (s1_ptr > s2_ptr)
	{
		i = n;
		while (i > 0)
		{
			s1_ptr[i - 1] = s2_ptr[i - 1];
			i--;
		}
	}
	else if (s1_ptr < s2_ptr)
		ft_memcpy(s1_ptr, s2_ptr, n);
	return (s1);
}
