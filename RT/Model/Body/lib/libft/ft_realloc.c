/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 13:43:19 by hshakula          #+#    #+#             */
/*   Updated: 2017/02/28 19:29:23 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *data, size_t old_size, size_t new_size)
{
	void *res;

	if (!new_size)
	{
		free(data);
		return (NULL);
	}
	else if (!data)
		return (malloc(new_size));
	else if (new_size <= old_size)
		return (data);
	else
	{
		res = malloc(new_size);
		ft_memcpy(res, data, old_size);
		return (res);
	}
}
