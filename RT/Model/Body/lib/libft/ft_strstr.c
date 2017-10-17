/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 13:43:19 by hshakula          #+#    #+#             */
/*   Updated: 2016/12/13 18:18:10 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	size_t		i;
	size_t		len1;
	size_t		len2;
	const char	*s1_ptr;
	const char	*s2_ptr;

	if (!*s1 && !*s2)
		return ((char*)s1);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	s1_ptr = s1;
	s2_ptr = s2;
	i = 0;
	while (i < len1)
	{
		if (!ft_memcmp(&s1_ptr[i], s2_ptr, len2))
			return (&((char *)s1_ptr)[i]);
		i++;
	}
	return (NULL);
}
