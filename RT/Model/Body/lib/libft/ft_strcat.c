/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 13:43:19 by hshakula          #+#    #+#             */
/*   Updated: 2016/12/12 17:43:39 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	size_t	i1;
	size_t	i2;
	size_t	len;
	char	*s1_ptr;

	s1_ptr = s1;
	len = ft_strlen(s1) + ft_strlen(s2);
	i1 = 0;
	i2 = ft_strlen(s1);
	while (i2 < len)
	{
		s1_ptr[i2] = ((char *)s2)[i1];
		i1++;
		i2++;
	}
	s1_ptr[i2] = '\0';
	return (s1);
}
