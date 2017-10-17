/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 19:56:40 by hshakula          #+#    #+#             */
/*   Updated: 2016/11/28 19:56:58 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*result;

	if (!(result = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		result->content = NULL;
		result->content_size = 0;
	}
	else
	{
		result->content = malloc(content_size);
		if (!result->content)
			return (NULL);
		ft_memcpy(result->content, (char*)content, content_size);
		result->content_size = content_size;
	}
	result->next = NULL;
	return (result);
}
