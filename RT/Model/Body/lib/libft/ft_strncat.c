/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 13:43:19 by hshakula          #+#    #+#             */
/*   Updated: 2016/12/12 17:43:39 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s1);
	while (i < n && s2[i])
	{
		s1[len] = ((char *)s2)[i];
		len++;
		i++;
	}
	s1[len] = '\0';
	return (s1);
}
