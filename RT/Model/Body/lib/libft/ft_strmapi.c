/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 15:03:49 by hshakula          #+#    #+#             */
/*   Updated: 2016/11/27 17:52:01 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*sptr;
	char	*str;
	int		i;

	if (!s || !f)
		return (NULL);
	sptr = (char*)s;
	if (!(str = (char*)malloc(ft_strlen((char*)s) + 1)))
		return (NULL);
	i = 0;
	while (sptr[i])
	{
		str[i] = f(i, sptr[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
