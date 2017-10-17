/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 13:43:19 by hshakula          #+#    #+#             */
/*   Updated: 2016/12/13 18:10:56 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;
	size_t	len1;

	i = 0;
	len = 0;
	len1 = ft_strlen(dst);
	while (dst[len] && len < size)
		len++;
	if (len >= size)
		return (size + ft_strlen(src));
	while (src[i] && i < (size - len1 - 1))
	{
		dst[len + i] = ((char *)src)[i];
		i++;
	}
	dst[len + i] = '\0';
	return (len + ft_strlen(src));
}
