/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 15:20:58 by hshakula          #+#    #+#             */
/*   Updated: 2016/11/27 17:40:57 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *str;

	if (!s1 || !s2)
		return (NULL);
	if (!(str = (char*)malloc(ft_strlen((char*)s1) + ft_strlen((char*)s2 + 1))))
		return (NULL);
	ft_strcpy(str, (char*)s1);
	ft_strcpy((str + ft_strlen((char*)s1)), (char*)s2);
	return (str);
}
