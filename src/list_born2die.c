/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_born2die.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:35:18 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/07/23 21:33:27 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		ft_del_all(t_lines **head)
{
	t_lines *curr;
	t_lines *tmp;

	curr = *head;
	while (curr != NULL)
	{
		tmp = curr;
		curr = curr->next;
		ft_memdel((void *)&tmp->str);
		ft_memdel((void *)&tmp);
	}
	*head = NULL;
	return (1);
}

void	ft_add_to_end(t_lines **head, char *str)
{
	t_lines *curr;

	if (!*head)
	{
		if (!(*head = (t_lines *)ft_memalloc(sizeof(t_lines))))
			errors_handler(4, NULL);
		(*head)->str = ft_strdup(str);
		(*head)->next = NULL;
	}
	else
	{
		curr = *head;
		while (curr && curr->next)
			curr = curr->next;
		if (!(curr->next = (t_lines *)ft_memalloc(sizeof(t_lines))))
			errors_handler(4, NULL);
		curr = curr->next;
		curr->str = ft_strdup(str);
		curr->next = NULL;
	}
}
