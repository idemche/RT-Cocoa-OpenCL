/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countwords.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 13:43:19 by hshakula          #+#    #+#             */
/*   Updated: 2016/12/17 14:53:27 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_countwords(char *str, char c)
{
	int i;
	int number_of_words;

	i = 0;
	number_of_words = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			number_of_words++;
			while (str[i] != c && str[i])
				i++;
		}
		else
			i++;
	}
	return (number_of_words);
}
