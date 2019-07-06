/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_born2die.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:35:18 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/04/02 18:57:53 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_del_all(t_lines **head)
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
}

void	ft_add_to_end(t_lines **head, char *str)
{
	t_lines *curr;

	if (!*head)
	{
		if (!(*head = (t_lines *)ft_memalloc(sizeof(t_lines))))
			errors_msg(4);
		(*head)->str = ft_strdup(str);
		(*head)->next = NULL;
	}
	else
	{
		curr = *head;
		while (curr && curr->next)
			curr = curr->next;
		if (!(curr->next = (t_lines *)ft_memalloc(sizeof(t_lines))))
			errors_msg(4);
		curr = curr->next;
		curr->str = ft_strdup(str);
		curr->next = NULL;
	}
}
