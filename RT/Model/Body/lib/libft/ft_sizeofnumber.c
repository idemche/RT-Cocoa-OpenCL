/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sizeofnumber.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 13:43:19 by hshakula          #+#    #+#             */
/*   Updated: 2016/12/17 14:53:46 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_sizeofnumber(int n)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = n;
	if (n == 0)
		return (1);
	while (nbr)
	{
		nbr /= 10;
		i++;
	}
	if (n < 0)
		i++;
	return (i);
}
