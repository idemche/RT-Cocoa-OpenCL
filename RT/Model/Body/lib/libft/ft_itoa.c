/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 13:43:19 by hshakula          #+#    #+#             */
/*   Updated: 2016/12/13 20:42:21 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(int n)
{
	int		nbr;
	int		len;
	char	*res;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	nbr = n;
	len = 0;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	len += ft_sizeofnumber(n);
	if (!(res = ft_strnew(len)))
		return (NULL);
	while (len--)
	{
		res[len] = (n % 10) + 48;
		n /= 10;
	}
	if (nbr < 0)
		res[0] = '-';
	return (res);
}
