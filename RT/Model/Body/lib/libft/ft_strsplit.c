/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 18:48:52 by hshakula          #+#    #+#             */
/*   Updated: 2016/11/29 19:09:34 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			**ft_strsplit(const char *s, char c)
{
	int		i;
	int		j;
	int		number_of_words;
	char	**result;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	number_of_words = ft_countwords((char*)s, c);
	if (!(result = (char**)malloc(sizeof(result) * (number_of_words + 2))))
		return (NULL);
	while (s[i] == c && s[i])
		i++;
	while (j < number_of_words && s[i])
	{
		result[j] = ft_getword((char*)s, c, &i);
		j++;
	}
	result[j] = NULL;
	return (result);
}
