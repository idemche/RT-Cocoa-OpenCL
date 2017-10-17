/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 19:55:49 by hshakula          #+#    #+#             */
/*   Updated: 2016/11/28 19:56:09 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddend(t_list **alst, t_list *new)
{
	t_list **lst;

	lst = (t_list**)alst;
	while ((*lst)->next)
		*lst = (*lst)->next;
	(*lst)->next = new;
}
