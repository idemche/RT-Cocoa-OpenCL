/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 15:36:03 by hshakula          #+#    #+#             */
/*   Updated: 2016/11/29 19:05:56 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*str;
	size_t	i;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen((char*)s);
	while (ft_isspace(s[len - 1]))
		len--;
	if (len == 0)
		return (ft_strdup(""));
	while (ft_isspace(*s))
	{
		len--;
		s++;
	}
	if (!(str = (char*)malloc(len + 1)))
		return (NULL);
	i = 0;
	while (i < len)
		str[i++] = *s++;
	str[i] = '\0';
	return (str);
}
