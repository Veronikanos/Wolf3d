/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 17:13:48 by vtlostiu          #+#    #+#             */
/*   Updated: 2018/11/17 17:13:50 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*current;
	t_list	*head;

	if (!(lst) || !(f))
		return (NULL);
	head = f(lst);
	current = head;
	while (lst->next)
	{
		current->next = f(lst->next);
		lst = lst->next;
		current = current->next;
	}
	return (head);
}
