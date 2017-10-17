/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 19:58:21 by hshakula          #+#    #+#             */
/*   Updated: 2016/11/28 20:14:55 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*tmp;
	t_list	*nlst;

	tmp = NULL;
	nlst = NULL;
	if (!lst)
		return (NULL);
	if (!(nlst = (t_list*)malloc(sizeof(t_list*))))
		return (NULL);
	nlst = f(ft_lstnew(lst->content, lst->content_size));
	tmp = nlst;
	lst = lst->next;
	while (lst)
	{
		tmp->next = f(ft_lstnew(lst->content, lst->content_size));
		tmp = tmp->next;
		lst = lst->next;
	}
	return (nlst);
}
