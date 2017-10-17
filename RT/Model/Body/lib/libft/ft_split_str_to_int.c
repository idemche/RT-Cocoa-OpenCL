/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_str_to_int.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 13:43:19 by hshakula          #+#    #+#             */
/*   Updated: 2017/09/30 20:54:25 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		size_of_word(char *s, char c)
{
	int		i;
	int		res;

	res = 0;
	i = 0;
	while (s[i] != c && s[i])
	{
		i++;
		res++;
	}
	return (res);
}

static void		put_int_in_tab(int nbr_of_w, char c, int *res, char *s)
{
	int		i;
	int		j;
	int		size;
	char	*tmp;

	size = 0;
	i = 0;
	j = 0;
	while (s[i] && j < nbr_of_w)
	{
		if ((s[i] == c && s[i + 1] != c && s[i + 1]) ||
			(s[0] != c && i == 0))
		{
			if (s[i] == c)
				i++;
			size = size_of_word(&s[i], c);
			tmp = ft_strsub(s, i, size);
			res[j] = ft_atoi(tmp);
			free(tmp);
			j++;
		}
		i++;
	}
}

int				*ft_strsplittoint(char const *s, char c)
{
	int		*res;
	int		nbr_of_w;
	int		i;

	if (!s)
		return (NULL);
	nbr_of_w = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if ((s[i] == c && s[i + 1] != c && s[i + 1]) ||
			(s[0] != c && i == 0))
			nbr_of_w++;
		i++;
	}
	res = (int *)malloc(sizeof(int) * nbr_of_w);
	if (res)
		put_int_in_tab(nbr_of_w, c, res, (char*)s);
	else
		return (NULL);
	return (res);
}
