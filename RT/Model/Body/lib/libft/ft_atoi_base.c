/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 20:00:48 by hshakula          #+#    #+#             */
/*   Updated: 2017/03/10 19:24:09 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isblank(int c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ');
}

static int	ind(char c, const char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int			ft_atoi_base(const char *nptr, const char *base)
{
	int		result;
	int		neg;
	int		blen;

	result = 0;
	blen = (int)ft_strlen(base);
	if (blen < 2)
		return (0);
	while (isblank(*nptr))
		nptr++;
	neg = *nptr == '-';
	if (*nptr == '+' || *nptr == '-')
		nptr++;
	while (ind(*nptr, base) < blen)
		result = result * blen - ind(*nptr++, base);
	return (neg ? result : -result);
}
