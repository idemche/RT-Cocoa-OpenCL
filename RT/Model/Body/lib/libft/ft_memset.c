/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 13:43:19 by hshakula          #+#    #+#             */
/*   Updated: 2016/12/13 18:13:19 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t len)
{
	size_t			i;
	char			*s_ptr;

	s_ptr = (char *)s;
	i = 0;
	if (!s)
		return (s);
	while (i < len)
	{
		s_ptr[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
