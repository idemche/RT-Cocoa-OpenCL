/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 13:43:19 by hshakula          #+#    #+#             */
/*   Updated: 2016/12/13 19:17:43 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int res;
	int i;
	int temp;

	i = 0;
	while (ft_isspace(str[i]) && str[i])
		i++;
	temp = i;
	if (str[i] == '+' || str[i] == '-')
		i++;
	res = 0;
	while (ft_isdigit(str[i]) && str[i])
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	if (str[temp] == '-')
		res *= -1;
	return (res);
}
