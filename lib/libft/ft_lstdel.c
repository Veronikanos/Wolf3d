/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 20:58:20 by vtlostiu          #+#    #+#             */
/*   Updated: 2018/11/16 20:58:38 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*nextl;

	if (!(alst) || !(del))
		return ;
	while (*alst)
	{
		nextl = (*alst)->next;
		del((*alst)->content, (*alst)->content_size);
		free(*alst);
		*alst = nextl;
	}
	*alst = NULL;
}
